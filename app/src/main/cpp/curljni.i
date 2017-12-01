%module(directors="1") CurlUtils

%include <std_string.i>

%include <typemaps.i>
%include <various.i>

%apply unsigned char *NIOBUFFER { unsigned char *buf };

%ignore CurlUtil::get(std::string url, std::function<void(int, std::string)>);

%feature("director",assumeoverride=1) Response;

%feature("director",assumeoverride=1) ByteResponse;




%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
%}
%include "CurlUtil.h"
%{
    #include "CurlUtil.h"
%}




