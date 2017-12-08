//fix ByteBuffer
%typemap(directorin, descriptor="Ljava/nio/ByteBuffer;") unsigned char *NIOBUFFER  {

    $input = JCALL2(NewDirectByteBuffer,jenv,$1,len);
}

SWIG_DIRECTOR_OWNED(ByteResponse)
SWIG_DIRECTOR_OWNED(Progress)
SWIG_DIRECTOR_OWNED(Response)

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

%typemap(check) SWIGTYPE *self %{
if (!$1) {
  SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException,
    "invalid native object; delete() likely already called");
  return $null;
}
%}

%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_ATTACH_CURRENT_THREAD_AS_DAEMON

%}

%include <stl.i>

%include <typemaps.i>

%include <various.i>

namespace std {
  %template(ParamMap) map<std::string,std::string>;
};

%apply unsigned char *NIOBUFFER { unsigned char *buf };

