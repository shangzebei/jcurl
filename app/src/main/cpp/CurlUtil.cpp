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







CurlUtil *CurlUtil::get(std::string url, Response *response) {

    auto curlutil = new CurlUtil();

    auto *request = new HttpRequest();
    request->setUrl(url);

    request->setRequestType(HttpRequest::Type::Get);

    request->setResponseCallback([=](CAHttpClient *client, HttpResponse *httpResponse) {
        if (response != nullptr) {
            response->callback(httpResponse->getResponseCode(),
                               httpResponse->getResponseData()->toString());
        }
    });

    curlutil->setHttpRequest(request);
    return curlutil;

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
        }
    });

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
        }
    });

    util->setHttpRequest(request);

    return util;
}

void CurlUtil::execute() {

//    if (_execute) {
//        return;
//    }
//    switch (_httpRequest->getRequestType()) {
//        case HttpRequest::Type::Get:
            CAHttpClient::getInstance(4)->send(getHttpRequest());
            _execute = true;
//            break;
//    }

}

void CurlUtil::setHttpRequest(HttpRequest *httpRequest) {
    _httpRequest = httpRequest;
}
extern void *_progress;
CurlUtil *CurlUtil::setProgress(Progress *progress) {
    _progress=progress;
    return this;
}

HttpRequest *CurlUtil::getHttpRequest() {
    return _httpRequest;
}


