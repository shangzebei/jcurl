//
// Created by chinamall on 2017/11/30.
//
#include<android/log.h>
#include "CurlUtil.h"

#define LOG    "curl"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__)


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

    CAHttpClient::getInstance(4)->sendImmediate(getHttpRequest());

    _execute = true;

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
            getHttpRequest()->setUrl(getHttpRequest()->getUrl() + ("?" + value));
        }
            break;
        case HttpRequest::Type::Post: {
            LOGD("%s", value.c_str());
            getHttpRequest()->setRequestData(value.c_str(), value.length());
        }
            break;
    }
    return this;
}

std::string CurlUtil::dealParam(std::map<std::string, std::string> key_value) {
    std::string getRul = "";
    if (!key_value.empty()) {
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

CurlUtil *CurlUtil::setHeader(std::string header) {
    auto headers = getHttpRequest()->getHeaders();
    headers.push_back(header);
    getHttpRequest()->setHeaders(headers);
    return this;
}


CurlUtil *CurlUtil::getFile(std::string url, std::string toPath) {
    auto util = new CurlUtil();
    auto *request = new HttpRequest();
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GetFile);
    auto file = fopen(toPath.c_str(), "wb");
    if (!file) {
        throw std::runtime_error(toPath + " not writable or miss permission ");
    }
    request->setFileToGet(file);
    util->_execute = false;
    util->setHttpRequest(request);
    return util;

}


