//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H


#include <iostream>
#include <functional>


#pragma once

class Response {

public:
    virtual void callback(int result, std::string s) {

    }
};

#pragma once

class ByteResponse {
public:
    virtual void callback(int result, unsigned char *buf) {

    }
};

#pragma once

class CurlUtil {
private:

    CurlUtil();

    virtual ~CurlUtil();

public:

    static CurlUtil *getInstance();

public:

    CurlUtil *get(std::string url, Response *response);

    CurlUtil *get(std::string url, std::function<void(int, std::string)>);

    CurlUtil *getBytes(std::string url, ByteResponse *response);


private:
};


static CurlUtil *curlUtil = nullptr;

#endif //JCURL_CURLUTIL_H
