//fix ByteBuffer
%typemap(directorin, descriptor="Ljava/nio/ByteBuffer;") unsigned char *NIOBUFFER  {

    $input = JCALL2(NewDirectByteBuffer,jenv,$1,len);
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

%insert("runtime") %{
    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_NO_DETACH_CURRENT_THREAD
%}

%include <std_string.i>

%include <typemaps.i>

%include <various.i>


%apply unsigned char *NIOBUFFER { unsigned char *buf };