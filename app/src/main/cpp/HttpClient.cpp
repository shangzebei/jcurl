
#include "HttpClient.h"
#include "CAData.h"
#include "ccUtils.h"
#include <queue>
#include <curl.h>
#include <map>
#include <string.h>
#include <cstdlib>


static std::map<ssize_t, CAHttpClient*> s_mHttpClient; // pointer to singleton

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

// Callback function used by libcurl for collect response data
static size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

// Callback function used by libcurl for collect header data
static size_t writeHeaderData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}


static int processGetTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processPostTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processPutTask(CAHttpClient* client,  CAHttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processDeleteTask(CAHttpClient* client,  CAHttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processPostFileTask(CAHttpClient* client,  CAHttpRequest *request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
// int processDownloadTask(CAHttpRequest *task, write_callback callback, void *stream, int32_t *errorCode);

// Worker thread
void CAHttpClient::networkThread()
{
    increaseThreadCount();
    
    while (true)
    {
        CAHttpRequest *request;
        
        // step 1: send http request if the requestQueue isn't empty
        {
            std::lock_guard<std::mutex> lock(_requestQueueMutex);
            while (_requestQueue.empty())
            {
                _sleepCondition.wait(_requestQueueMutex);
            }
            request = _requestQueue.at(0);
            _requestQueue.erase(_requestQueue.begin());
        }
        
        if (request == _requestSentinel) {
            break;
        }
        
        // step 2: libcurl sync access
        
        // Create a CAHttpResponse object, the default setting is http access failed
        CAHttpResponse *response = new (std::nothrow) CAHttpResponse(request);
        
        processResponse(response, _responseMessage);
        
        
        // add response packet into queue
        _responseQueueMutex.lock();
        _responseQueue.push_back(response);
        _responseQueueMutex.unlock();
        
        _schedulerMutex.lock();
        this->dispatchResponseCallbacks();
//        if (nullptr != _scheduler)
//        {
//            _scheduler->performFunctionInUIThread([=]
//            {
//                this->dispatchResponseCallbacks();
//            });
//        }
        _schedulerMutex.unlock();
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    _requestQueueMutex.lock();
    _requestQueue.clear();
    _requestQueueMutex.unlock();
    
    _responseQueueMutex.lock();
    _responseQueue.clear();
    _responseQueueMutex.unlock();
    
    decreaseThreadCountAndMayDeleteThis();
}

// Worker thread
void CAHttpClient::networkThreadAlone(CAHttpRequest* request, CAHttpResponse* response)
{
    increaseThreadCount();
    
    char responseMessage[RESPONSE_BUFFER_SIZE] = { 0 };
    processResponse(response, responseMessage);
    
    _schedulerMutex.lock();


    auto& callback=request->getCallback();

    if (nullptr != callback) {
        callback(this,response);
    }
//    if (nullptr != _scheduler)
//    {
//        _scheduler->performFunctionInUIThread([this, response, request]{
//            const auto& callback = request->getCallback();
//
//            if (callback != nullptr)
//            {
//                callback(this, response);
//            }
////            response->release();
////            // do not release in other thread
////            request->release();
//        });
//    }
    _schedulerMutex.unlock();
    
    decreaseThreadCountAndMayDeleteThis();
}

//Configure curl's timeout property
static bool configureCURL(CAHttpClient* client, CURL* handle, char* errorBuffer)
{
    if (!handle) {
        return false;
    }
    
    int32_t code;
    code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, client->getTimeoutForRead());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, client->getTimeoutForConnect());
    if (code != CURLE_OK) {
        return false;
    }
    
    std::string sslCaFilename = client->getSSLVerification();
    if (sslCaFilename.empty()) {
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    } else {
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(handle, CURLOPT_CAINFO, sslCaFilename.c_str());
    }
    
    // FIXED #3224: The subthread of CCCAHttpClient interrupts main thread if timeout comes.
    // Document is here: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTNOSIGNAL
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
    
    curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
    
    return true;
}

class CURLRaii
{
    /// Instance of CURL
    CURL *_curl;
    /// Keeps custom header data
    curl_slist *_headers;
public:
    CURLRaii()
    : _curl(curl_easy_init())
    , _headers(nullptr)
    {
    }
    
    ~CURLRaii()
    {
        if (_curl)
            curl_easy_cleanup(_curl);
        /* free the linked list for header data */
        if (_headers)
            curl_slist_free_all(_headers);
    }
    
    template <class T>
    bool setOption(CURLoption option, T data)
    {
        return CURLE_OK == curl_easy_setopt(_curl, option, data);
    }
    
    /**
     * @brief Inits CURL instance for common usage
     * @param request Null not allowed
     * @param callback Response write callback
     * @param stream Response write stream
     */
    bool init(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void* stream, write_callback headerCallback, void* headerStream, char* errorBuffer)
    {
        if (!_curl)
            return false;
        if (!configureCURL(client, _curl, errorBuffer))
            return false;
        
        /* get custom header data (if set) */
        std::vector<std::string> headers=request->getHeaders();
        if(!headers.empty())
        {
            /* append custom headers one by one */
            for (std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
                _headers = curl_slist_append(_headers,it->c_str());
            /* set custom headers for curl */
            if (!setOption(CURLOPT_HTTPHEADER, _headers))
                return false;
        }
        std::string cookieFilename = client->getCookieFilename();
        if (!cookieFilename.empty()) {
            if (!setOption(CURLOPT_COOKIEFILE, cookieFilename.c_str())) {
                return false;
            }
            if (!setOption(CURLOPT_COOKIEJAR, cookieFilename.c_str())) {
                return false;
            }
        }
        
        return setOption(CURLOPT_URL, request->getUrl())
        && setOption(CURLOPT_WRITEFUNCTION, callback)
        && setOption(CURLOPT_WRITEDATA, stream)
        && setOption(CURLOPT_HEADERFUNCTION, headerCallback)
        && setOption(CURLOPT_HEADERDATA, headerStream);
        
    }
    
    /// @param responseCode Null not allowed
    bool perform(long *responseCode)
    {
        if (CURLE_OK != curl_easy_perform(_curl))
            return false;
        CURLcode code = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, responseCode);
        if (code != CURLE_OK || !(*responseCode >= 200 && *responseCode < 300)) {
//            CCLOG("ERROR!!! Curl curl_easy_getinfo failed: %s", curl_easy_strerror(code));
            return false;
        }
        // Get some mor data.
        
        return true;
    }
};

//Process Get Request
static int processGetTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
    && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
    && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process POST Request
static int processPostTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
    && curl.setOption(CURLOPT_POST, 1)
    && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
    && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
    && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process PUT Request
static int processPutTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
    && curl.setOption(CURLOPT_CUSTOMREQUEST, "PUT")
    && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
    && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
    && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process DELETE Request
static int processDeleteTask(CAHttpClient* client, CAHttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
    && curl.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
    && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
    && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process POSTFILE Request
static int processPostFileTask(CAHttpClient* client,  CAHttpRequest *request, write_callback callback, void *stream, long *responseCode, write_callback headerCallback, void *headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer);
    if (!ok)
        return 1;
    
    curl_httppost* pFormPost = NULL;
    curl_httppost* pLastElem = NULL;
    
    curl_formadd(&pFormPost, &pLastElem, CURLFORM_COPYNAME, "filepath", CURLFORM_FILE,
                 request->getFileNameToPost(), CURLFORM_CONTENTTYPE, "application/octet-stream", CURLFORM_END);
    
    ssize_t requestDataSize = request->getRequestDataSize();
    if (requestDataSize>0)
    {
        std::string strReq = request->getRequestData();
        strReq.resize(request->getRequestDataSize());
        std::vector<std::string> vv = Parse2StrVector(strReq, "&");
        for (int i = 0; i < vv.size(); i++)
        {
            std::vector<std::string> v = Parse2StrVector(vv[i], "=", true);
            if (v.size() == 2)
            {
                curl_formadd(&pFormPost, &pLastElem, CURLFORM_COPYNAME, v[0].c_str(), CURLFORM_COPYCONTENTS, v[1].c_str(), CURLFORM_END);
            }
        }
        curl_formadd(&pFormPost, &pLastElem, CURLFORM_COPYNAME, "act", CURLFORM_COPYCONTENTS, "end", CURLFORM_END);
    }
    
    ok = curl.setOption(CURLOPT_HTTPPOST, pFormPost)
    && curl.perform(responseCode);
    
    if (pFormPost)
    {
        curl_formfree(pFormPost);
        pFormPost = NULL;
    }
    return ok ? 0 : 1;
}

// CAHttpClient implementation
CAHttpClient* CAHttpClient::getInstance(ssize_t thread_id)
{
    if (s_mHttpClient.find(thread_id) == s_mHttpClient.end())
    {
        s_mHttpClient[thread_id] = new (std::nothrow) CAHttpClient(thread_id);
    }
    
    return s_mHttpClient.at(thread_id);
}

void CAHttpClient::destroyInstance(ssize_t thread_id)
{
    if (s_mHttpClient.find(thread_id) == s_mHttpClient.end())
    {
//        CCLOG("CAHttpClient singleton is nullptr");
        return;
    }
    
//    CCLOG("CAHttpClient::destroyInstance begin");
    auto thiz = s_mHttpClient.at(thread_id);
    s_mHttpClient.erase(thread_id);
    
    thiz->_schedulerMutex.lock();
    thiz->_schedulerMutex.unlock();
    
    thiz->_requestQueueMutex.lock();
    thiz->_requestQueue.push_back(thiz->_requestSentinel);
    thiz->_requestQueueMutex.unlock();
    
    thiz->_sleepCondition.notify_one();
    thiz->decreaseThreadCountAndMayDeleteThis();
    
//    CCLOG("CAHttpClient::destroyInstance() finished!");
}

void CAHttpClient::destroyAllInstance()
{
    for (auto& var : s_mHttpClient)
    {
        auto thiz = var.second;
        
        thiz->_schedulerMutex.lock();
        thiz->_schedulerMutex.unlock();
        
        thiz->_requestQueueMutex.lock();
        thiz->_requestQueue.push_back(thiz->_requestSentinel);
        thiz->_requestQueueMutex.unlock();
        
        thiz->_sleepCondition.notify_one();
        thiz->decreaseThreadCountAndMayDeleteThis();
    }
    s_mHttpClient.clear();
}

void CAHttpClient::enableCookies(const char* cookieFile)
{
    std::lock_guard<std::mutex> lock(_cookieFileMutex);
    if (cookieFile)
    {
        _cookieFilename = std::string(cookieFile);
    }
    else
    {
        _cookieFilename = ("cookieFile.txt");
    }
}

void CAHttpClient::setSSLVerification(const std::string& caFile)
{
    std::lock_guard<std::mutex> lock(_sslCaFileMutex);
    _sslCaFilename = caFile;
}

CAHttpClient::CAHttpClient(ssize_t thread_id)
: _thread_id(thread_id)
,_timeoutForConnect(30)
, _timeoutForRead(60)
, _isInited(false)
, _threadCount(0)
, _requestSentinel(new CAHttpRequest())
, _cookie(nullptr)
{
//    CCLOG("In the constructor of CAHttpClient!");
    memset(_responseMessage, 0, RESPONSE_BUFFER_SIZE * sizeof(char));
    increaseThreadCount();
}

CAHttpClient::~CAHttpClient()
{
    _requestSentinel = nullptr;
//    CC_SAFE_RELEASE(_requestSentinel);
//    CCLOG("CAHttpClient destructor");
}

//Lazy create semaphore & mutex & thread
bool CAHttpClient::lazyInitThreadSemphore()
{
    if (_isInited)
    {
        return true;
    }
    else
    {
        auto t = std::thread([=]
        {
            this->networkThread();
        });
        t.detach();
        _isInited = true;
    }
    
    return true;
}

//Add a get task to queue
void CAHttpClient::send(CAHttpRequest* request)
{
    if (false == lazyInitThreadSemphore())
    {
        return;
    }
    
    if (!request)
    {
        return;
    }
    request->setThreadID(_thread_id);

    _requestQueueMutex.lock();
    _requestQueue.push_back(request);
    _requestQueueMutex.unlock();
    
    // Notify thread start to work
    _sleepCondition.notify_one();
}

void CAHttpClient::sendImmediate(CAHttpRequest* request)
{
    if(!request)
    {
        return;
    }
    
//    request->retain();
    // Create a CAHttpResponse object, the default setting is http access failed
    CAHttpResponse *response = new (std::nothrow) CAHttpResponse(request);
    
    auto t = std::thread(&CAHttpClient::networkThreadAlone, this, request, response);
    t.detach();
}

// Poll and notify main thread if responses exists in queue
void CAHttpClient::dispatchResponseCallbacks()
{
    // log("CCCAHttpClient::dispatchResponseCallbacks is running");
    //occurs when cocos thread fires but the network thread has already quited
    CAHttpResponse* response = nullptr;
    
    _responseQueueMutex.lock();
    if (!_responseQueue.empty())
    {
        response = _responseQueue.at(0);
        _responseQueue.erase(_responseQueue.begin());
    }
    _responseQueueMutex.unlock();
    
    if (response)
    {
        CAHttpRequest *request = response->getHttpRequest();
        const auto& callback = request->getCallback();

        if (callback != nullptr)
        {
            callback(this, response);
        }

//        response->release();
//        // do not release in other thread
//        request->release();
    }
}

// Process Response
void CAHttpClient::processResponse(CAHttpResponse* response, char* responseMessage)
{
    auto request = response->getHttpRequest();
    long responseCode = -1;
    int retValue = 0;
    
    std::vector<char> responseData;
    std::vector<char> responseHeader;
    // Process the request -> get response packet
    switch (request->getRequestType())
    {
        case CAHttpRequest::Type::Get: // HTTP GET
            retValue = processGetTask(this, request,
                                      writeData,
                                      &responseData,
                                      &responseCode,
                                      writeHeaderData,
                                      &responseHeader,
                                      responseMessage);
            break;
            
        case CAHttpRequest::Type::Post: // HTTP POST
            retValue = processPostTask(this, request,
                                       writeData,
                                       &responseData,
                                       &responseCode,
                                       writeHeaderData,
                                       &responseHeader,
                                       responseMessage);
            break;
            
        case CAHttpRequest::Type::Put:
            retValue = processPutTask(this, request,
                                      writeData,
                                      &responseData,
                                      &responseCode,
                                      writeHeaderData,
                                      &responseHeader,
                                      responseMessage);
            break;
            
        case CAHttpRequest::Type::Delete:
            retValue = processDeleteTask(this, request,
                                         writeData,
                                         &responseData,
                                         &responseCode,
                                         writeHeaderData,
                                         &responseHeader,
                                         responseMessage);
            break;
        case CAHttpRequest::Type::PostFile:
            retValue = processPostFileTask(this, request,
                                           writeData,
                                           &responseData,
                                           &responseCode,
                                           writeHeaderData,
                                           &responseHeader,
                                           responseMessage);
            break;
        default:
//            CCASSERT(true, "CCCAHttpClient: unknown request type, only GET and POSt are supported");
            break;
    }
    
    ssize_t c_responseDataLength = responseData.size();
    unsigned char* c_responseData = (unsigned char*)malloc(c_responseDataLength + 1);
    c_responseData[c_responseDataLength] = '\0';
    memcpy((void*)c_responseData, (const void*)responseData.data(), c_responseDataLength);
    
    CAData* ca_responseData = new CAData();
    ca_responseData->fastSet(c_responseData, c_responseDataLength);
    response->setResponseData(ca_responseData);

    ssize_t c_responseHeaderLength = responseHeader.size();
    unsigned char* c_responseHeader = (unsigned char*)malloc(c_responseHeaderLength + 1);
    c_responseHeader[c_responseHeaderLength] = '\0';
    memcpy((void*)c_responseHeader, (const void*)responseHeader.data(), c_responseHeaderLength);
    
    CAData* ca_responseHeader = new CAData();
    ca_responseHeader->fastSet(c_responseHeader, c_responseHeaderLength);
    response->setResponseHeader(ca_responseHeader);

    // write data to CAHttpResponse
    response->setResponseCode(responseCode);
    if (retValue != 0)
    {
        response->setSucceed(false);
        response->setErrorBuffer(responseMessage);
    }
    else
    {
        response->setSucceed(true);
    }
}

void CAHttpClient::increaseThreadCount()
{
    _threadCountMutex.lock();
    ++_threadCount;
    _threadCountMutex.unlock();
}

void CAHttpClient::decreaseThreadCountAndMayDeleteThis()
{
    bool needDeleteThis = false;
    _threadCountMutex.lock();
    --_threadCount;
    if (0 == _threadCount)
    {
        needDeleteThis = true;
    }
    
    _threadCountMutex.unlock();
    if (needDeleteThis)
    {
        delete this;
    }
}

void CAHttpClient::setTimeoutForConnect(int value)
{
    std::lock_guard<std::mutex> lock(_timeoutForConnectMutex);
    _timeoutForConnect = value;
}

int CAHttpClient::getTimeoutForConnect()
{
    std::lock_guard<std::mutex> lock(_timeoutForConnectMutex);
    return _timeoutForConnect;
}

void CAHttpClient::setTimeoutForRead(int value)
{
    std::lock_guard<std::mutex> lock(_timeoutForReadMutex);
    _timeoutForRead = value;
}

int CAHttpClient::getTimeoutForRead()
{
    std::lock_guard<std::mutex> lock(_timeoutForReadMutex);
    return _timeoutForRead;
}

const std::string& CAHttpClient::getCookieFilename()
{
    std::lock_guard<std::mutex> lock(_cookieFileMutex);
    return _cookieFilename;
}

const std::string& CAHttpClient::getSSLVerification()
{
    std::lock_guard<std::mutex> lock(_sslCaFileMutex);
    return _sslCaFilename;
}



