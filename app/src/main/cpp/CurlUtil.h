//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H


#include <iostream>
#include <functional>
#include "HttpClient.h"
#include "HttpRequest.h"

#pragma once

class Response {

public:
    virtual void callback(int result, std::string s) {

    }
};

#pragma once

class ByteResponse {
public:
    virtual void callback(int result, unsigned char *buf,size_t len) {

    }
};
#pragma once
class Progress{
public:
    virtual void progress(unsigned long long unow,unsigned long long utotal,unsigned long long dnow,unsigned long long dtotal) {

    }
};

#pragma once

class CurlUtil {
private:

    CurlUtil();

    virtual ~CurlUtil();



public:

    static CurlUtil *get(std::string url, Response *response);

    static CurlUtil *get(std::string url, std::function<void(int, std::string)>);

    static CurlUtil *getBytes(std::string url, ByteResponse *response);

    CurlUtil * setProgress(Progress *progress);

    void execute();

private:

    void setHttpRequest( HttpRequest *httpRequest);

    HttpRequest *getHttpRequest();

    HttpRequest *_httpRequest;

    bool _execute = false;
};


#endif //JCURL_CURLUTIL_H
