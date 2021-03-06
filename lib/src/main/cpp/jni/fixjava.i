//fix ByteBuffer
%typemap(directorin, descriptor="Ljava/nio/ByteBuffer;") unsigned char *NIOBUFFER  {

    $input = JCALL2(NewDirectByteBuffer,jenv,$1,len);
}
%typemap(javadirectorin) unsigned char *NIOBUFFER "$jniinput"

SWIG_DIRECTOR_OWNED(ByteResponse)
SWIG_DIRECTOR_OWNED(Progress)
SWIG_DIRECTOR_OWNED(Response)


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

%exception %{
     try {
         $action
     } catch (std::exception& e) {
         SWIG_JavaException(jenv,SWIG_RuntimeError,e.what());
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
  %template(ParamArray) vector<std::string>;
  %template(ParamArray) vector<std::string>;
};

%apply unsigned char *NIOBUFFER { unsigned char *buf };

