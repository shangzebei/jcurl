//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H


#include <iostream>

using namespace std;

class Response{
public:
    Response();

public:
    virtual void callback(int result, string s);
};


class CurlUtil {
private:
    CurlUtil();

    virtual ~CurlUtil();

public:
    static CurlUtil *getInstance();

public:
    CurlUtil * get(string url,Response* response);

private:
};



static CurlUtil *curlUtil = nullptr;

#endif //JCURL_CURLUTIL_H
