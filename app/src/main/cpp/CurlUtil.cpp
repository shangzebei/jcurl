//
// Created by chinamall on 2017/11/30.
//
#include<android/log.h>

#define LOG    "curl" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) //
#include "CurlUtil.h"
#include "HttpClient.h"
#include "HttpRequest.h"

CurlUtil *CurlUtil::getInstance() {
    if (curlUtil == nullptr) {
        curlUtil = new CurlUtil();
    }
    return curlUtil;
}

string CurlUtil::get(string url,Response& response) {
    HttpRequest* request = new HttpRequest();
    request->setUrl(url);

    request->setRequestType(HttpRequest::Type::Get);

    LOGD("go");
    request->setResponseCallback([&](CAHttpClient* client, HttpResponse* httpResponse){
//        LOGD("%s",httpResponse->getResponseData()->toString().c_str());
//        response->callback(0,httpResponse->getResponseData()->toString());
            response.callback(0,"aaaa");


    });

    CAHttpClient::getInstance(4)->send(request);


    return "my name is shang";
}

CurlUtil::CurlUtil() {

}

CurlUtil::~CurlUtil() {

}

void Response::callback(int result, string s) {

}
