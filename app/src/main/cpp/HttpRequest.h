
#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <vector>
#include <functional>

/**
 * @addtogroup network
 * @{
 */


class CAHttpClient;
class HttpResponse;

/**
 * Defines the object which users must packed for CAHttpClient::send(HttpRequest*) method.
 * Please refer to tests/test-cpp/Classes/ExtensionTest/NetworkTest/CAHttpClientTest.cpp as a sample
 * @since v2.0.2
 *
 * @lua NA
 */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef DELETE
#undef DELETE
#endif
#endif

class  HttpRequest
{
public:
    /**
     * The HttpRequest type enum used in the HttpRequest::setRequestType.
     */
    enum class Type
    {
        Get = 0,
        Post,
        PostFile,
        Put,
        Delete,
        Unkown,
    };
    
    /**
     *  Constructor.
     *   Because HttpRequest object will be used between UI thread and network thread,
     requestObj->autorelease() is forbidden to avoid crashes in AutoreleasePool
     new/retain/release still works, which means you need to release it manually
     Please refer to CAHttpRequestTest.cpp to find its usage.
     */
    HttpRequest()
    : _requestType(Type::Unkown)
    , _pCallback(nullptr)
    {
    }
    
    /** Destructor. */
    virtual ~HttpRequest()
    {
    }
    

    // setter/getters for properties
    
    /**
     * Set request type of HttpRequest object before being sent,now it support the enum value of HttpRequest::Type.
     *
     * @param type the request type.
     */
    inline void setRequestType(Type type)
    {
        _requestType = type;
    }
    
    /**
     * Get the request type of HttpRequest object.
     *
     * @return HttpRequest::Type.
     */
    inline Type getRequestType() const
    {
        return _requestType;
    }
    
    /**
     * Set the url address of HttpRequest object.
     * The url value could be like these: "http://httpbin.org/ip" or "https://httpbin.org/get"
     *
     * @param url the string object.
     */
    inline void setUrl(const std::string& url)
    {
        _url = url;
    }
    
    /**
     * Get the url address of HttpRequest object.
     *
     * @return const char* the pointer of _url.
     */
    inline const char* getUrl() const
    {
        return _url.c_str();
    }
    
    /**
     * Set the request data of HttpRequest object.
     *
     * @param buffer the buffer of request data, it support binary data.
     * @param len    the size of request data.
     */
    inline void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    }
    
    /**
     * Get the request data pointer of HttpRequest object.
     *
     * @return char* the request data pointer.
     */
    inline char* getRequestData()
    {
        if(!_requestData.empty())
            return _requestData.data();
        
        return nullptr;
    }
    
    /**
     * Get the size of request data
     *
     * @return ssize_t the size of request data
     */
    inline ssize_t getRequestDataSize() const
    {
        return _requestData.size();
    }

    // setter/getters for properties
    inline void setFileNameToPost(const std::string& fileName)
    {
        _fileNameToPost = fileName;
    }
    
    inline const char* getFileNameToPost()
    {
        return _fileNameToPost.c_str();
    }
    /**
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @param callback the Callback function.
     */
    inline void setResponseCallback(const std::function<void(CAHttpClient* client, HttpResponse* response)>& callback)
    {
        _pCallback = callback;
    }

    /**
     * Get Callback callback function.
     *
     * @return const Callback& callback function.
     */
    inline const std::function<void(CAHttpClient* client, HttpResponse* response)>& getCallback() const
    {
        return _pCallback;
    }
    
    /**
     * Set custom-defined headers.
     *
     * @param headers The string vector of custom-defined headers.
     */
    inline void setHeaders(const std::vector<std::string>& headers)
    {
        _headers = headers;
    }
    
    /**
     * Get custom headers.
     *
     * @return std::vector<std::string> the string vector of custom-defined headers.
     */
    inline std::vector<std::string> getHeaders() const
    {
        return _headers;
    }
    
    inline void setThreadID(ssize_t threadID)
    {
        _threadID = threadID;
    };
    
    inline ssize_t getThreadID()
    {
        return _threadID;
    };
    
protected:
    // properties
    Type                        _requestType;    /// kCAHttpRequestGet, kCAHttpRequestPost or other enums
    std::string                 _url;            /// target url that this request is sent to
    std::vector<char>           _requestData;    /// used for POST
    std::function<void(CAHttpClient* client, HttpResponse* response)>
                                _pCallback;      /// C++11 style callbacks
    std::vector<std::string>    _headers;              /// custom http headers
    std::string					_fileNameToPost;
    ssize_t                     _threadID;
};


// end group
/// @}

#endif //__HTTP_REQUEST_H__

