//
// Created by chinamall on 2017/11/30.
//

#ifndef JCURL_CURLUTIL_H
#define JCURL_CURLUTIL_H





#include <iostream>
using namespace std;

class  CurlUtil {
private:
    CurlUtil();

    virtual ~CurlUtil();

public:
    static CurlUtil* getInstance();
    string get(string url);

public:

};
static CurlUtil *curlUtil= nullptr;

#endif //JCURL_CURLUTIL_H
