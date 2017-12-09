//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H


#include <iostream>
#include <functional>
#include <map>
#include "HttpClient.h"
#include "HttpRequest.h"
#pragma ParamFormData
class ParamFormData{
public:
    enum class Type {
        TEXT = 0,
        FILE

    };
    std::string name;
    std::vector<std::string> files;
    std::string value;
    Type type;
};

#pragma once

class Response {

public:
    virtual void callback(int result, std::string s) {

    }
};


#pragma once

class ByteResponse {
public:
    virtual void callback(int result, unsigned char *buf, size_t len) {

    }

private:
    std::string _tag;
};

#pragma once

class Progress {
public:
    virtual void progress(long long unow, long long utotal, long long dnow, long long dtotal) {

    }

    void setTag(std::string tag) {
        _tag = tag;
    }

    std::string getTag(){
        return _tag;
    }

private:
    std::string _tag;
};

#pragma once

class CurlUtil {
private:

    CurlUtil();

    virtual ~CurlUtil();


public:

    static CurlUtil *get(std::string url, Response *response);

    static CurlUtil *deleteJ(std::string url, Response *response);

    static CurlUtil *put(std::string url, Response *response);

    static CurlUtil *post(std::string url, Response *response);

    static CurlUtil *get(std::string url, std::function<void(int, std::string)>);

    static CurlUtil *getBytes(std::string url, ByteResponse *response);

    static CurlUtil *getFile(std::string url, std::string toPath);

    static CurlUtil *postFormData(std::string url, Response *response);

    static CurlUtil *uploadMultiFile(std::string url, std::map<std::string,std::string> key_file,Response *response);

    static CurlUtil *uploadMultiFile(std::string url, std::map<std::string,ParamFormData *> key_file,Response *response);

    CurlUtil *setProgress(Progress *progress);

    CurlUtil *setParam(std::map<std::string,std::string> key_value);

    CurlUtil *setParamData(std::string data);

    CurlUtil *setHeader(std::string header);

    void execute(std::string tag);

    void execute();

    void setTag(std::string tag);

    std::string getTag();

private:

    void setHttpRequest(HttpRequest *httpRequest);

    HttpRequest *getHttpRequest();

    HttpRequest *_httpRequest;

    bool _execute = false;

    std::string _tag;

    static CurlUtil *process(std::string url, HttpRequest::Type type, Response *response);

    std::string dealParam(std::map<std::string, std::string> key_value);


};


#endif //JCURL_CURLUTIL_H
