%module(directors="1") CurlUtils
%feature("director") Response;
%include "std_string.i"
%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
%}
%include "CurlUtil.h"
%{
    #include "CurlUtil.h"
%}




