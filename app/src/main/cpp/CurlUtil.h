//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H


#include <iostream>

using namespace std;
class Response;
class CurlUtil {
private:
    CurlUtil();

    virtual ~CurlUtil();

public:
    static CurlUtil *getInstance();

public:

    string get(string url, Response &response);
};

class Response{
public:
    void callback(int result, string s);

};

static CurlUtil *curlUtil = nullptr;

#endif //JCURL_CURLUTIL_H
