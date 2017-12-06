%module(directors="1") CurlUtils
#if defined(SWIGJAVA)
%include "jni/momory.i"
%include "jni/fixjava.i"
#endif

%ignore CurlUtil::get(std::string url, std::function<void(int, std::string)>);

%feature("director",assumeoverride=1) Response;

%feature("director",assumeoverride=1) ByteResponse;

%feature("director",assumeoverride=1) Progress;

%include "CurlUtil.h"
%{
    #include "CurlUtil.h"
%}




