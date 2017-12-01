%module(directors="1") CurlUtils

%feature("director",assumeoverride=1) Response;

%feature("director",assumeoverride=1) ByteResponse;

%include "std_string.i"

%ignore CurlUtil::get(string url, std::function<void(int, string)> func);

%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
%}
%include "CurlUtil.h"
%{
    #include "CurlUtil.h"
%}




