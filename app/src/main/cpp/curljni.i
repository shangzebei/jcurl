%module(directors="1") CurlUtils
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "stl.i"
%include "typemaps.i"
%include "CurlUtil.h"
%{
#include "CurlUtil.h"
%}
%feature("director") Response;
%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    //#define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
%}


