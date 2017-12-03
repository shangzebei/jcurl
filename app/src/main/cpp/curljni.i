%module(directors="1") CurlUtils

%typemap(directorin, descriptor="Ljava/nio/ByteBuffer;") unsigned char *NIOBUFFER  {
    $input = JCALL2(NewDirectByteBuffer,jenv,$1,strlen($1));
}

%typemap(javadirectorin) unsigned char *NIOBUFFER "$jniinput"

%{
static inline void printException(JNIEnv * jenv, jthrowable throwable){
    if (throwable) {
        jclass throwclz = jenv->FindClass("java/lang/Throwable");
        if (throwclz) {
            jmethodID printStackMethod = jenv->GetMethodID(throwclz, "printStackTrace", "()V");
            if (printStackMethod) {
                jenv->CallNonvirtualVoidMethod(throwable, throwclz, printStackMethod);
            }
        }
    }
}
%}
%feature("director:except") %{
    jthrowable $error = jenv->ExceptionOccurred();
    if ($error) {
        jenv->ExceptionClear();
        printException(jenv, $error);
        throw Swig::DirectorException(jenv, $error);
    }
%}

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




