//
// Created by chinamall on 2017/11/30.
//
#include<android/log.h>
#include "CurlUtil.h"

#define LOG    "curl" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) //


CurlUtil *CurlUtil::process(std::string url, HttpRequest::Type type, Response *response) {
    auto curlutil = new CurlUtil();

    auto *request = new HttpRequest();
    request->setUrl(url);

    request->setRequestType(type);

    request->setResponseCallback([=](CAHttpClient *client, HttpResponse *httpResponse) {
        if (response != nullptr) {
            response->callback(httpResponse->getResponseCode(),
                               httpResponse->getResponseData()->toString());
            httpResponse->getResponseData()->clear();
            delete response;
        }
    });
    curlutil->_execute = false;
    curlutil->setHttpRequest(request);
    return curlutil;
}


CurlUtil *CurlUtil::get(std::string url, Response *response) {
    return process(url, HttpRequest::Type::Get, response);
}

CurlUtil::CurlUtil() {

}

CurlUtil::~CurlUtil() {
    LOGD("CurlUtil::~CurlUtil");
}

CurlUtil *CurlUtil::get(std::string url, std::function<void(int, std::string)> func) {

    auto util = new CurlUtil();

    auto *request = new HttpRequest();

    request->setUrl(url);

    request->setRequestType(HttpRequest::Type::Get);

    request->setResponseCallback([=](CAHttpClient *client, HttpResponse *httpResponse) {
        if (func != nullptr) {
            func(httpResponse->getResponseCode(), httpResponse->getResponseData()->toString());
            httpResponse->getResponseData()->clear();
        }
    });
    util->_execute = false;

    util->setHttpRequest(request);

    return util;
}

CurlUtil *CurlUtil::getBytes(std::string url, ByteResponse *response) {

    auto util = new CurlUtil();

    auto *request = new HttpRequest();

    request->setUrl(url);

    request->setRequestType(HttpRequest::Type::Get);

    request->setResponseCallback([=](CAHttpClient *client, HttpResponse *httpResponse) {
        if (response != nullptr) {
            auto data = httpResponse->getResponseData();
            response->callback(httpResponse->getResponseCode(), data->getBytes(),
                               data->getLength());
            data->clear();
            delete response;

        }
    });

    util->_execute = false;
    util->setHttpRequest(request);

    return util;
}


void CurlUtil::setHttpRequest(HttpRequest *httpRequest) {
    _httpRequest = httpRequest;
}


CurlUtil *CurlUtil::setProgress(Progress *progress) {
    _httpRequest->setProgress(progress);
    return this;
}

HttpRequest *CurlUtil::getHttpRequest() {
    return _httpRequest;
}

void CurlUtil::execute(std::string tag) {

    if (_execute) {
        return;
    }
    setTag(tag);
    switch (_httpRequest->getRequestType()) {
        case HttpRequest::Type::Get:
            CAHttpClient::getInstance(4)->sendImmediate(getHttpRequest());
            _execute = true;
            break;
    }
}

void CurlUtil::setTag(std::string tag) {
    _tag = tag;
}

std::string CurlUtil::getTag() {
    return _tag;
}

void CurlUtil::execute() {
    execute("curl");
}

CurlUtil *CurlUtil::setParam(std::map<std::string, std::string> key_value) {
    auto value = dealParam(key_value);
    switch (_httpRequest->getRequestType()) {
        case HttpRequest::Type::Get: {
            getHttpRequest()->setUrl(getHttpRequest()->getUrl() + value);
        }
            break;
        case HttpRequest::Type::Post: {
            getHttpRequest()->setRequestData(value.c_str(), value.length());

        }
            break;
    }
    return this;
}

std::string CurlUtil::dealParam(std::map<std::string, std::string> key_value) {
    std::string getRul = "";
    if (!key_value.empty()) {
        getRul += "?";

        std::map<std::string, std::string>::iterator itr = key_value.begin();

        do {
            getRul = getRul + itr->first + "=" + itr->second;
            itr++;
            if (itr == key_value.end()) {
                break;
            }
            getRul = getRul + "&";
        } while (1);
    }
    return getRul;
}

CurlUtil *CurlUtil::post(std::string url, Response *response) {
    return process(url, HttpRequest::Type::Post, response);
}


