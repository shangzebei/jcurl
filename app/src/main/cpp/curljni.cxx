/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.4
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#define SWIGJAVA
#define SWIG_DIRECTORS


#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif



/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
  };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  jenv->ExceptionClear();
  excep = jenv->FindClass(except_ptr->java_exception);
  if (excep)
    jenv->ThrowNew(excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


    //#define DEBUG_DIRECTOR_OWNED
    #define SWIG_JAVA_NO_DETACH_CURRENT_THREAD

/* -----------------------------------------------------------------------------
 * director.swg
 *
 * This file contains support for director classes so that Java proxy
 * methods can be called from C++.
 * ----------------------------------------------------------------------------- */

#if defined(DEBUG_DIRECTOR_OWNED) || defined(DEBUG_DIRECTOR_EXCEPTION)
#include <iostream>
#endif

#include <exception>

namespace Swig {

  /* Java object wrapper */
  class JObjectWrapper {
  public:
    JObjectWrapper() : jthis_(NULL), weak_global_(true) {
    }

    ~JObjectWrapper() {
      jthis_ = NULL;
      weak_global_ = true;
    }

    bool set(JNIEnv *jenv, jobject jobj, bool mem_own, bool weak_global) {
      if (!jthis_) {
        weak_global_ = weak_global || !mem_own; // hold as weak global if explicitly requested or not owned
        if (jobj)
          jthis_ = weak_global_ ? jenv->NewWeakGlobalRef(jobj) : jenv->NewGlobalRef(jobj);
#if defined(DEBUG_DIRECTOR_OWNED)
        std::cout << "JObjectWrapper::set(" << jobj << ", " << (weak_global ? "weak_global" : "global_ref") << ") -> " << jthis_ << std::endl;
#endif
        return true;
      } else {
#if defined(DEBUG_DIRECTOR_OWNED)
        std::cout << "JObjectWrapper::set(" << jobj << ", " << (weak_global ? "weak_global" : "global_ref") << ") -> already set" << std::endl;
#endif
        return false;
      }
    }

    jobject get(JNIEnv *jenv) const {
#if defined(DEBUG_DIRECTOR_OWNED)
      std::cout << "JObjectWrapper::get(";
      if (jthis_)
        std::cout << jthis_;
      else
        std::cout << "null";
      std::cout << ") -> return new local ref" << std::endl;
#endif
      return (jthis_ ? jenv->NewLocalRef(jthis_) : jthis_);
    }

    void release(JNIEnv *jenv) {
#if defined(DEBUG_DIRECTOR_OWNED)
      std::cout << "JObjectWrapper::release(" << jthis_ << "): " << (weak_global_ ? "weak global ref" : "global ref") << std::endl;
#endif
      if (jthis_) {
        if (weak_global_) {
          if (jenv->IsSameObject(jthis_, NULL) == JNI_FALSE)
            jenv->DeleteWeakGlobalRef((jweak)jthis_);
        } else
          jenv->DeleteGlobalRef(jthis_);
      }

      jthis_ = NULL;
      weak_global_ = true;
    }

    /* Only call peek if you know what you are doing wrt to weak/global references */
    jobject peek() {
      return jthis_;
    }

    /* Java proxy releases ownership of C++ object, C++ object is now
       responsible for destruction (creates NewGlobalRef to pin Java proxy) */
    void java_change_ownership(JNIEnv *jenv, jobject jself, bool take_or_release) {
      if (take_or_release) {  /* Java takes ownership of C++ object's lifetime. */
        if (!weak_global_) {
          jenv->DeleteGlobalRef(jthis_);
          jthis_ = jenv->NewWeakGlobalRef(jself);
          weak_global_ = true;
        }
      } else {
	/* Java releases ownership of C++ object's lifetime */
        if (weak_global_) {
          jenv->DeleteWeakGlobalRef((jweak)jthis_);
          jthis_ = jenv->NewGlobalRef(jself);
          weak_global_ = false;
        }
      }
    }

  private:
    /* pointer to Java object */
    jobject jthis_;
    /* Local or global reference flag */
    bool weak_global_;
  };

  /* Local JNI reference deleter */
  class LocalRefGuard {
    JNIEnv *jenv_;
    jobject jobj_;

    // non-copyable
    LocalRefGuard(const LocalRefGuard &);
    LocalRefGuard &operator=(const LocalRefGuard &);
  public:
    LocalRefGuard(JNIEnv *jenv, jobject jobj): jenv_(jenv), jobj_(jobj) {}
    ~LocalRefGuard() {
      if (jobj_)
        jenv_->DeleteLocalRef(jobj_);
    }
  };

  /* director base class */
  class Director {
    /* pointer to Java virtual machine */
    JavaVM *swig_jvm_;

  protected:
#if defined (_MSC_VER) && (_MSC_VER<1300)
    class JNIEnvWrapper;
    friend class JNIEnvWrapper;
#endif
    /* Utility class for managing the JNI environment */
    class JNIEnvWrapper {
      const Director *director_;
      JNIEnv *jenv_;
      int env_status;
    public:
      JNIEnvWrapper(const Director *director) : director_(director), jenv_(0), env_status(0) {
#if defined(__ANDROID__)
        JNIEnv **jenv = &jenv_;
#else
        void **jenv = (void **)&jenv_;
#endif
        env_status = director_->swig_jvm_->GetEnv((void **)&jenv_, JNI_VERSION_1_2);
#if defined(SWIG_JAVA_ATTACH_CURRENT_THREAD_AS_DAEMON)
        // Attach a daemon thread to the JVM. Useful when the JVM should not wait for
        // the thread to exit upon shutdown. Only for jdk-1.4 and later.
        director_->swig_jvm_->AttachCurrentThreadAsDaemon(jenv, NULL);
#else
        director_->swig_jvm_->AttachCurrentThread(jenv, NULL);
#endif
      }
      ~JNIEnvWrapper() {
#if !defined(SWIG_JAVA_NO_DETACH_CURRENT_THREAD)
        // Some JVMs, eg jdk-1.4.2 and lower on Solaris have a bug and crash with the DetachCurrentThread call.
        // However, without this call, the JVM hangs on exit when the thread was not created by the JVM and creates a memory leak.
        if (env_status == JNI_EDETACHED)
          director_->swig_jvm_->DetachCurrentThread();
#endif
      }
      JNIEnv *getJNIEnv() const {
        return jenv_;
      }
    };

    /* Java object wrapper */
    JObjectWrapper swig_self_;

    /* Disconnect director from Java object */
    void swig_disconnect_director_self(const char *disconn_method) {
      JNIEnvWrapper jnienv(this) ;
      JNIEnv *jenv = jnienv.getJNIEnv() ;
      jobject jobj = swig_self_.get(jenv);
      LocalRefGuard ref_deleter(jenv, jobj);
#if defined(DEBUG_DIRECTOR_OWNED)
      std::cout << "Swig::Director::disconnect_director_self(" << jobj << ")" << std::endl;
#endif
      if (jobj && jenv->IsSameObject(jobj, NULL) == JNI_FALSE) {
        jmethodID disconn_meth = jenv->GetMethodID(jenv->GetObjectClass(jobj), disconn_method, "()V");
        if (disconn_meth) {
#if defined(DEBUG_DIRECTOR_OWNED)
          std::cout << "Swig::Director::disconnect_director_self upcall to " << disconn_method << std::endl;
#endif
          jenv->CallVoidMethod(jobj, disconn_meth);
        }
      }
    }

  public:
    Director(JNIEnv *jenv) : swig_jvm_((JavaVM *) NULL), swig_self_() {
      /* Acquire the Java VM pointer */
      jenv->GetJavaVM(&swig_jvm_);
    }

    virtual ~Director() {
      JNIEnvWrapper jnienv(this) ;
      JNIEnv *jenv = jnienv.getJNIEnv() ;
      swig_self_.release(jenv);
    }

    bool swig_set_self(JNIEnv *jenv, jobject jself, bool mem_own, bool weak_global) {
      return swig_self_.set(jenv, jself, mem_own, weak_global);
    }

    jobject swig_get_self(JNIEnv *jenv) const {
      return swig_self_.get(jenv);
    }

    // Change C++ object's ownership, relative to Java
    void swig_java_change_ownership(JNIEnv *jenv, jobject jself, bool take_or_release) {
      swig_self_.java_change_ownership(jenv, jself, take_or_release);
    }
  };


  // Utility classes and functions for exception handling.

  // Simple holder for a Java string during exception handling, providing access to a c-style string
  class JavaString {
  public:
    JavaString(JNIEnv *jenv, jstring jstr) : jenv_(jenv), jstr_(jstr), cstr_(0) {
      if (jenv_ && jstr_)
	cstr_ = (const char *) jenv_->GetStringUTFChars(jstr_, NULL);
    }

    ~JavaString() {
      if (jenv_ && jstr_ && cstr_)
	jenv_->ReleaseStringUTFChars(jstr_, cstr_);
    }

    const char *c_str(const char *null_string = "null JavaString") const {
      return cstr_ ? cstr_ : null_string;
    }

  private:
    // non-copyable
    JavaString(const JavaString &);
    JavaString &operator=(const JavaString &);

    JNIEnv *jenv_;
    jstring jstr_;
    const char *cstr_;
  };

  // Helper class to extract the exception message from a Java throwable
  class JavaExceptionMessage {
  public:
    JavaExceptionMessage(JNIEnv *jenv, jthrowable throwable) : message_(jenv, exceptionMessageFromThrowable(jenv, throwable)) {
    }

    const char *message() const {
      return message_.c_str("Could not get exception message in JavaExceptionMessage");
    }

  private:
    // non-copyable
    JavaExceptionMessage(const JavaExceptionMessage &);
    JavaExceptionMessage &operator=(const JavaExceptionMessage &);

    // Get exception message by calling Java method Throwable.getMessage()
    static jstring exceptionMessageFromThrowable(JNIEnv *jenv, jthrowable throwable) {
      jstring jmsg = NULL;
      if (jenv && throwable) {
	jenv->ExceptionClear(); // Cannot invoke methods with any pending exceptions
	jclass throwclz = jenv->GetObjectClass(throwable);
	if (throwclz) {
	  // All Throwable classes have a getMessage() method, so call it to extract the exception message
	  jmethodID getMessageMethodID = jenv->GetMethodID(throwclz, "getMessage", "()Ljava/lang/String;");
	  if (getMessageMethodID)
	    jmsg = (jstring)jenv->CallObjectMethod(throwable, getMessageMethodID);
	}
	if (jmsg == NULL && jenv->ExceptionCheck())
	  jenv->ExceptionClear();
      }
      return jmsg;
    }

    JavaString message_;
  };

  // C++ Exception class for handling Java exceptions thrown during a director method Java upcall
  class DirectorException : public std::exception {
  public:

    // Construct exception from a Java throwable
    DirectorException(JNIEnv *jenv, jthrowable throwable) : classname_(0), msg_(0) {

      // Call Java method Object.getClass().getName() to obtain the throwable's class name (delimited by '/')
      if (throwable) {
	jclass throwclz = jenv->GetObjectClass(throwable);
	if (throwclz) {
	  jclass clzclz = jenv->GetObjectClass(throwclz);
	  if (clzclz) {
	    jmethodID getNameMethodID = jenv->GetMethodID(clzclz, "getName", "()Ljava/lang/String;");
	    if (getNameMethodID) {
	      jstring jstr_classname = (jstring)(jenv->CallObjectMethod(throwclz, getNameMethodID));
              // Copy strings, since there is no guarantee that jenv will be active when handled
              if (jstr_classname) {
                JavaString jsclassname(jenv, jstr_classname);
                const char *classname = jsclassname.c_str(0);
                if (classname)
                  classname_ = copypath(classname);
              }
	    }
	  }
	}
      }

      JavaExceptionMessage exceptionmsg(jenv, throwable);
      msg_ = copystr(exceptionmsg.message());
    }

    // More general constructor for handling as a java.lang.RuntimeException
    DirectorException(const char *msg) : classname_(0), msg_(copystr(msg ? msg : "Unspecified DirectorException message")) {
    }

    ~DirectorException() throw() {
      delete[] classname_;
      delete[] msg_;
    }

    const char *what() const throw() {
      return msg_;
    }

    // Reconstruct and raise/throw the Java Exception that caused the DirectorException
    // Note that any error in the JNI exception handling results in a Java RuntimeException
    void raiseJavaException(JNIEnv *jenv) const {
      if (jenv) {
	jenv->ExceptionClear();

	jmethodID ctorMethodID = 0;
	jclass throwableclass = 0;
        if (classname_) {
          throwableclass = jenv->FindClass(classname_);
          if (throwableclass)
            ctorMethodID = jenv->GetMethodID(throwableclass, "<init>", "(Ljava/lang/String;)V");
	}

	if (ctorMethodID) {
	  jenv->ThrowNew(throwableclass, what());
	} else {
	  SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, what());
	}
      }
    }

  private:
    static char *copypath(const char *srcmsg) {
      char *target = copystr(srcmsg);
      for (char *c=target; *c; ++c) {
        if ('.' == *c)
          *c = '/';
      }
      return target;
    }

    static char *copystr(const char *srcmsg) {
      char *target = 0;
      if (srcmsg) {
	int msglen = strlen(srcmsg) + 1;
	target = new char[msglen];
	strncpy(target, srcmsg, msglen);
      }
      return target;
    }

    const char *classname_;
    const char *msg_;
  };

  // Helper method to determine if a Java throwable matches a particular Java class type
  bool ExceptionMatches(JNIEnv *jenv, jthrowable throwable, const char *classname) {
    bool matches = false;

    if (throwable && jenv && classname) {
      // Exceptions need to be cleared for correct behavior.
      // The caller of ExceptionMatches should restore pending exceptions if desired -
      // the caller already has the throwable.
      jenv->ExceptionClear();

      jclass clz = jenv->FindClass(classname);
      if (clz) {
	jclass classclz = jenv->GetObjectClass(clz);
	jmethodID isInstanceMethodID = jenv->GetMethodID(classclz, "isInstance", "(Ljava/lang/Object;)Z");
	if (isInstanceMethodID) {
	  matches = jenv->CallBooleanMethod(clz, isInstanceMethodID, throwable) != 0;
	}
      }

#if defined(DEBUG_DIRECTOR_EXCEPTION)
      if (jenv->ExceptionCheck()) {
        // Typically occurs when an invalid classname argument is passed resulting in a ClassNotFoundException
        JavaExceptionMessage exc(jenv, jenv->ExceptionOccurred());
        std::cout << "Error: ExceptionMatches: class '" << classname << "' : " << exc.message() << std::endl;
      }
#endif
    }
    return matches;
  }
}

namespace Swig {
  namespace {
    jclass jclass_CurlUtilsJNI = NULL;
    jmethodID director_methids[2];
  }
}

#include <string>


    #include "CurlUtil.h"



/* ---------------------------------------------------
 * C++ director class methods
 * --------------------------------------------------- */

#include "curljni.h"

SwigDirector_Response::SwigDirector_Response(JNIEnv *jenv) : Response(), Swig::Director(jenv) {
}

void SwigDirector_Response::callback(int result, std::string s) {
  JNIEnvWrapper swigjnienv(this) ;
  JNIEnv * jenv = swigjnienv.getJNIEnv() ;
  jobject swigjobj = (jobject) NULL ;
  jint jresult  ;
  jstring js  ;
  
  if (!swig_override[0]) {
    Response::callback(result,s);
    return;
  }
  swigjobj = swig_get_self(jenv);
  if (swigjobj && jenv->IsSameObject(swigjobj, NULL) == JNI_FALSE) {
    jresult = (jint) result;
    js = jenv->NewStringUTF((&s)->c_str());
    Swig::LocalRefGuard s_refguard(jenv, js); 
    jenv->CallStaticVoidMethod(Swig::jclass_CurlUtilsJNI, Swig::director_methids[0], swigjobj, jresult, js);
    jthrowable swigerror = jenv->ExceptionOccurred();
    if (swigerror) {
      jenv->ExceptionClear();
      throw Swig::DirectorException(jenv, swigerror);
    }
    
  } else {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null upcall object in Response::callback ");
  }
  if (swigjobj) jenv->DeleteLocalRef(swigjobj);
}

void SwigDirector_Response::swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global) {
  static struct {
    const char *mname;
    const char *mdesc;
    jmethodID base_methid;
  } methods[] = {
    {
      "callback", "(ILjava/lang/String;)V", NULL 
    }
  };
  
  static jclass baseclass = 0 ;
  
  if (swig_set_self(jenv, jself, swig_mem_own, weak_global)) {
    if (!baseclass) {
      baseclass = jenv->FindClass("s/docker/com/jcurl/Response");
      if (!baseclass) return;
      baseclass = (jclass) jenv->NewGlobalRef(baseclass);
    }
    bool derived = (jenv->IsSameObject(baseclass, jcls) ? false : true);
    for (int i = 0; i < 1; ++i) {
      if (!methods[i].base_methid) {
        methods[i].base_methid = jenv->GetMethodID(baseclass, methods[i].mname, methods[i].mdesc);
        if (!methods[i].base_methid) return;
      }
      swig_override[i] = derived;
    }
  }
}


SwigDirector_ByteResponse::SwigDirector_ByteResponse(JNIEnv *jenv) : ByteResponse(), Swig::Director(jenv) {
}

void SwigDirector_ByteResponse::callback(int result, unsigned char *buf) {
  JNIEnvWrapper swigjnienv(this) ;
  JNIEnv * jenv = swigjnienv.getJNIEnv() ;
  jobject swigjobj = (jobject) NULL ;
  jint jresult  ;
  jobject jbuf = 0 ;
  
  if (!swig_override[0]) {
    ByteResponse::callback(result,buf);
    return;
  }
  swigjobj = swig_get_self(jenv);
  if (swigjobj && jenv->IsSameObject(swigjobj, NULL) == JNI_FALSE) {
    jresult = (jint) result;
    jbuf =  buf;
    jenv->CallStaticVoidMethod(Swig::jclass_CurlUtilsJNI, Swig::director_methids[1], swigjobj, jresult, jbuf);
    jthrowable swigerror = jenv->ExceptionOccurred();
    if (swigerror) {
      jenv->ExceptionClear();
      throw Swig::DirectorException(jenv, swigerror);
    }
    
  } else {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null upcall object in ByteResponse::callback ");
  }
  if (swigjobj) jenv->DeleteLocalRef(swigjobj);
}

void SwigDirector_ByteResponse::swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global) {
  static struct {
    const char *mname;
    const char *mdesc;
    jmethodID base_methid;
  } methods[] = {
    {
      "callback", "(Ijava.nio.ByteBuffer)V", NULL 
    }
  };
  
  static jclass baseclass = 0 ;
  
  if (swig_set_self(jenv, jself, swig_mem_own, weak_global)) {
    if (!baseclass) {
      baseclass = jenv->FindClass("s/docker/com/jcurl/ByteResponse");
      if (!baseclass) return;
      baseclass = (jclass) jenv->NewGlobalRef(baseclass);
    }
    bool derived = (jenv->IsSameObject(baseclass, jcls) ? false : true);
    for (int i = 0; i < 1; ++i) {
      if (!methods[i].base_methid) {
        methods[i].base_methid = jenv->GetMethodID(baseclass, methods[i].mname, methods[i].mdesc);
        if (!methods[i].base_methid) return;
      }
      swig_override[i] = derived;
    }
  }
}



#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_Response_1callback(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jstring jarg3) {
  Response *arg1 = (Response *) 0 ;
  int arg2 ;
  std::string arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Response **)&jarg1; 
  arg2 = (int)jarg2; 
  if(!jarg3) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return ;
  } 
  const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0); 
  if (!arg3_pstr) return ;
  (&arg3)->assign(arg3_pstr);
  jenv->ReleaseStringUTFChars(jarg3, arg3_pstr); 
  (arg1)->callback(arg2,arg3);
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_Response_1callbackSwigExplicitResponse(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jstring jarg3) {
  Response *arg1 = (Response *) 0 ;
  int arg2 ;
  std::string arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Response **)&jarg1; 
  arg2 = (int)jarg2; 
  if(!jarg3) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return ;
  } 
  const char *arg3_pstr = (const char *)jenv->GetStringUTFChars(jarg3, 0); 
  if (!arg3_pstr) return ;
  (&arg3)->assign(arg3_pstr);
  jenv->ReleaseStringUTFChars(jarg3, arg3_pstr); 
  (arg1)->Response::callback(arg2,arg3);
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_new_1Response(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  Response *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (Response *)new SwigDirector_Response(jenv);
  *(Response **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_delete_1Response(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  Response *arg1 = (Response *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Response **)&jarg1; 
  delete arg1;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_Response_1director_1connect(JNIEnv *jenv, jclass jcls, jobject jself, jlong objarg, jboolean jswig_mem_own, jboolean jweak_global) {
  Response *obj = *((Response **)&objarg);
  (void)jcls;
  SwigDirector_Response *director = dynamic_cast<SwigDirector_Response *>(obj);
  if (director) {
    director->swig_connect_director(jenv, jself, jenv->GetObjectClass(jself), (jswig_mem_own == JNI_TRUE), (jweak_global == JNI_TRUE));
  }
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_Response_1change_1ownership(JNIEnv *jenv, jclass jcls, jobject jself, jlong objarg, jboolean jtake_or_release) {
  Response *obj = *((Response **)&objarg);
  SwigDirector_Response *director = dynamic_cast<SwigDirector_Response *>(obj);
  (void)jcls;
  if (director) {
    director->swig_java_change_ownership(jenv, jself, jtake_or_release ? true : false);
  }
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_ByteResponse_1callback(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jobject jarg3) {
  ByteResponse *arg1 = (ByteResponse *) 0 ;
  int arg2 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(ByteResponse **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    arg3 = (unsigned char *) jenv->GetDirectBufferAddress(jarg3); 
    if (arg3 == NULL) {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, "Unable to get address of a java.nio.ByteBuffer direct byte buffer. Buffer must be a direct buffer and not a non-direct buffer.");  
    }  
  }
  (arg1)->callback(arg2,arg3);
  
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_ByteResponse_1callbackSwigExplicitByteResponse(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jobject jarg3) {
  ByteResponse *arg1 = (ByteResponse *) 0 ;
  int arg2 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(ByteResponse **)&jarg1; 
  arg2 = (int)jarg2; 
  {
    arg3 = (unsigned char *) jenv->GetDirectBufferAddress(jarg3); 
    if (arg3 == NULL) {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, "Unable to get address of a java.nio.ByteBuffer direct byte buffer. Buffer must be a direct buffer and not a non-direct buffer.");  
    }  
  }
  (arg1)->ByteResponse::callback(arg2,arg3);
  
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_new_1ByteResponse(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  ByteResponse *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (ByteResponse *)new SwigDirector_ByteResponse(jenv);
  *(ByteResponse **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_delete_1ByteResponse(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  ByteResponse *arg1 = (ByteResponse *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(ByteResponse **)&jarg1; 
  delete arg1;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_ByteResponse_1director_1connect(JNIEnv *jenv, jclass jcls, jobject jself, jlong objarg, jboolean jswig_mem_own, jboolean jweak_global) {
  ByteResponse *obj = *((ByteResponse **)&objarg);
  (void)jcls;
  SwigDirector_ByteResponse *director = dynamic_cast<SwigDirector_ByteResponse *>(obj);
  if (director) {
    director->swig_connect_director(jenv, jself, jenv->GetObjectClass(jself), (jswig_mem_own == JNI_TRUE), (jweak_global == JNI_TRUE));
  }
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_ByteResponse_1change_1ownership(JNIEnv *jenv, jclass jcls, jobject jself, jlong objarg, jboolean jtake_or_release) {
  ByteResponse *obj = *((ByteResponse **)&objarg);
  SwigDirector_ByteResponse *director = dynamic_cast<SwigDirector_ByteResponse *>(obj);
  (void)jcls;
  if (director) {
    director->swig_java_change_ownership(jenv, jself, jtake_or_release ? true : false);
  }
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_CurlUtil_1getInstance(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  CurlUtil *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (CurlUtil *)CurlUtil::getInstance();
  *(CurlUtil **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_CurlUtil_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jlong jarg3, jobject jarg3_) {
  jlong jresult = 0 ;
  CurlUtil *arg1 = (CurlUtil *) 0 ;
  std::string arg2 ;
  Response *arg3 = (Response *) 0 ;
  CurlUtil *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg3_;
  arg1 = *(CurlUtil **)&jarg1; 
  if(!jarg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return 0;
  } 
  const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0); 
  if (!arg2_pstr) return 0;
  (&arg2)->assign(arg2_pstr);
  jenv->ReleaseStringUTFChars(jarg2, arg2_pstr); 
  arg3 = *(Response **)&jarg3; 
  result = (CurlUtil *)(arg1)->get(arg2,arg3);
  *(CurlUtil **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_CurlUtil_1getBytes(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jstring jarg2, jlong jarg3, jobject jarg3_) {
  jlong jresult = 0 ;
  CurlUtil *arg1 = (CurlUtil *) 0 ;
  std::string arg2 ;
  ByteResponse *arg3 = (ByteResponse *) 0 ;
  CurlUtil *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg3_;
  arg1 = *(CurlUtil **)&jarg1; 
  if(!jarg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null string");
    return 0;
  } 
  const char *arg2_pstr = (const char *)jenv->GetStringUTFChars(jarg2, 0); 
  if (!arg2_pstr) return 0;
  (&arg2)->assign(arg2_pstr);
  jenv->ReleaseStringUTFChars(jarg2, arg2_pstr); 
  arg3 = *(ByteResponse **)&jarg3; 
  result = (CurlUtil *)(arg1)->getBytes(arg2,arg3);
  *(CurlUtil **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_curlUtil_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  CurlUtil *arg1 = (CurlUtil *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(CurlUtil **)&jarg1; 
  curlUtil = arg1;
}


SWIGEXPORT jlong JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_curlUtil_1get(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  CurlUtil *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (CurlUtil *)curlUtil;
  *(CurlUtil **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_s_docker_com_jcurl_CurlUtilsJNI_swig_1module_1init(JNIEnv *jenv, jclass jcls) {
  int i;
  
  static struct {
    const char *method;
    const char *signature;
  } methods[2] = {
    {
      "SwigDirector_Response_callback", "(Ls/docker/com/jcurl/Response;ILjava/lang/String;)V" 
    },
    {
      "SwigDirector_ByteResponse_callback", "(Ls/docker/com/jcurl/ByteResponse;Ijava.nio.ByteBuffer)V" 
    }
  };
  Swig::jclass_CurlUtilsJNI = (jclass) jenv->NewGlobalRef(jcls);
  if (!Swig::jclass_CurlUtilsJNI) return;
  for (i = 0; i < (int) (sizeof(methods)/sizeof(methods[0])); ++i) {
    Swig::director_methids[i] = jenv->GetStaticMethodID(jcls, methods[i].method, methods[i].signature);
    if (!Swig::director_methids[i]) return;
  }
}


#ifdef __cplusplus
}
#endif

