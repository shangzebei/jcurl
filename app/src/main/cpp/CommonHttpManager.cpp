
#include <algorithm>
#include <json_lib.h>
#include "CommonHttpManager.h"

#define REQUEST_JSON_COUNT 2
#define REQUEST_IMAGE_COUNT 2
#define CC_BREAK_IF(cond)           if(cond) break
static const char* loading_bg              = "";
static const char* loading_icon            = "";


static bool compareHttpClient(CAHttpClient* itr1, CAHttpClient* itr2)
{
    return (itr1)->getRequestCount() < (itr2)->getRequestCount();
}


#pragma CommonImageCacheManager





#pragma CommonHttpManager

CommonHttpManager* _HttpManager = nullptr;

CommonHttpManager* CommonHttpManager::getInstance()
{
    if (_HttpManager == nullptr)
    {
        _HttpManager = new CommonHttpManager();
    }
    return _HttpManager;
}

void CommonHttpManager::destroyInstance()
{
    if (_HttpManager)
    {
        delete _HttpManager;
        _HttpManager = nullptr;
    }
}

CommonHttpManager::CommonHttpManager()
{
    for (int i=0; i<REQUEST_JSON_COUNT; i++)
    {
        CAHttpClient* httpClient = CAHttpClient::getInstance(15 - i);
        httpClient->setTimeoutForConnect(5);
        httpClient->setTimeoutForRead(5);
        m_pHttpJsonClients.push_back(httpClient);
    }
    for (int i=REQUEST_JSON_COUNT; i<REQUEST_JSON_COUNT + REQUEST_IMAGE_COUNT; i++)
    {
        CAHttpClient* httpClient = CAHttpClient::getInstance(15 - i);
        httpClient->setTimeoutForConnect(5);
        httpClient->setTimeoutForRead(5);
        m_pHttpImageClients.push_back(httpClient);
    }
    

//    std::string fullPath = FileUtils::getInstance()->getWritablePath() + "commonHttpManager.db";
//    localStorageInit(fullPath.c_str());

}



CommonHttpManager::~CommonHttpManager()
{
    for (int i=0; i<REQUEST_JSON_COUNT + REQUEST_IMAGE_COUNT; i++)
    {
        CAHttpClient::destroyInstance(15 - i);
    }
    m_pHttpJsonClients.clear();
    m_pHttpImageClients.clear();
}


void CommonHttpManager::send_get(const std::string& url,std::map<std::string,
                                 std::string> key_value,
                                 const JsonCallback& callback)
{
    std::string getRul = url;
    if (!key_value.empty())
    {
        getRul += "?";
        
        std::map<std::string, std::string>::iterator itr = key_value.begin();
        
        do
        {
            getRul = getRul + itr->first + "=" + itr->second;
            itr++;
            CC_BREAK_IF(itr==key_value.end());
            getRul = getRul + "&";
        }
        while (1);
    }
//    CCLog("url==%s",getRul.c_str());
    CAHttpRequest* httpRequest = new CAHttpRequest();
    httpRequest->setUrl(getRul.c_str());
    httpRequest->setRequestType(CAHttpRequest::Type::Get);
    
    httpRequest->setResponseCallback([=](CAHttpClient* client, CAHttpResponse* response)
    {
        if (response->isSucceed())
        {
            std::string data(response->getResponseData()->toString());
            if (!data.empty())
            {
//                localStorageSetItem(MD5(url + "AAA").md5().c_str(), data.c_str());
                
//                CCLog("\n \n \n---------HttpResponse--json---------\n<<<\n%s\n>>>\n--------------END--------------\n \n \n",data.c_str());
                
                CSJson::Reader read;
                CSJson::Value root;
                bool succ = read.parse(data, root);
                if (succ == false)
                {
//                    CCLog("GetParseError \n");
                }
                
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Succeed, root);
                }
                
            }
            else
            {
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
                }
            }
            
        }
        else
        {
//            const char* data = localStorageGetItem(MD5(url + "AAA").md5().c_str());
            
//            do
//            {
//                CC_BREAK_IF(data == NULL);
//                CSJson::Reader read;
//                CSJson::Value root;
//                bool succ = read.parse(data, root);
//                if (succ == false)
//                {
//                    break;
//                }
//
//                if (callback)
//                {
//                    callback(CommonHttpManager::ResponseStatus::Succeed, root);
//                }
//                return;
//            }
//            while (0);
            
            if (callback)
            {
                callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
            }
        }

    });
    
    std::sort(m_pHttpJsonClients.begin(), m_pHttpJsonClients.end(), compareHttpClient);
    m_pHttpJsonClients.front()->send(httpRequest);

}



void CommonHttpManager::send_post(const std::string& url,
                                  std::map<std::string,std::string> key_value,
                                  const JsonCallback& callback)
{
    std::string postData;
    if (!key_value.empty())
    {
        std::map<std::string, std::string>::iterator itr = key_value.begin();
        
        do
        {
            postData = postData + itr->first + "=" + itr->second;
            itr++;
            CC_BREAK_IF(itr==key_value.end());
            postData = postData + "&";
        }
        while (1);
    }
//    CCLog("send_post url:%s postData:%s",url.c_str(), postData.c_str());

    CAHttpRequest* httpRequest = new CAHttpRequest();
    httpRequest->setUrl(url.c_str());
    httpRequest->setRequestType(CAHttpRequest::Type::Post);
    httpRequest->setRequestData(postData.c_str(), (unsigned int)postData.length());
    
    httpRequest->setResponseCallback([=](CAHttpClient* client, CAHttpResponse* response)
    {
        if (response->isSucceed())
        {
            std::string data(response->getResponseData()->toString());
            if (!data.empty())
            {
//                CCLog("\n \n \n---------HttpResponse--json---------\n<<<\n%s\n>>>\n--------------END--------------\n \n \n", data.c_str());
                
                CSJson::Reader read;
                CSJson::Value root;
                bool succ = read.parse(data, root);
                if (succ == false)
                {
//                    CCLog("GetParseError \n");
                }
                
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Succeed, root);
                }
            }
            else
            {
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
                }
            }
            
        }
        else
        {
//            CCLog("ResponseCode:%ld, Error:%s",response->getResponseCode(),response->getErrorBuffer());
            if (callback)
            {
                callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
            }
        }
    });
    
    std::sort(m_pHttpJsonClients.begin(), m_pHttpJsonClients.end(), compareHttpClient);
    m_pHttpJsonClients.front()->send(httpRequest);


}

void CommonHttpManager::send_postFile(const std::string& url,
                                      std::map<std::string, std::string> key_value,
                                      const std::string& file,
                                      const JsonCallback& callback)
{
    std::string postData;
    if (!key_value.empty())
    {
        std::map<std::string, std::string>::iterator itr = key_value.begin();
        
        do
        {
            postData = postData + itr->first + "=" + itr->second;
            itr++;
            CC_BREAK_IF(itr==key_value.end());
            postData = postData + "&";
        }
        while (1);
    }
    CAHttpRequest* httpRequest = new CAHttpRequest();
    httpRequest->setUrl(url.c_str());
    httpRequest->setRequestType(CAHttpRequest::Type::PostFile);
    httpRequest->setRequestData(postData.c_str(), (unsigned int)postData.length());
    httpRequest->setFileNameToPost(file);

    httpRequest->setResponseCallback([=](CAHttpClient* client, CAHttpResponse* response)
    {
        if (response->isSucceed())
        {
            std::string data(response->getResponseData()->toString());
            if (!data.empty())
            {

                CSJson::Reader read;
                CSJson::Value root;
                bool succ = read.parse(data, root);
                if (!succ)
                {
                }
                
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Succeed, root);
                }
            }
            else
            {
                if (callback)
                {
                    callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
                }
            }
            
        }
        else
        {
//            CCLog("ResponseCode:%ld, Error:%s",response->getResponseCode(),response->getErrorBuffer());
            if (callback)
            {
                callback(CommonHttpManager::ResponseStatus::Faild, CSJson::Value());
            }
        }
    });
    
    std::sort(m_pHttpJsonClients.begin(), m_pHttpJsonClients.end(), compareHttpClient);
    m_pHttpJsonClients.front()->send(httpRequest);

    
}
