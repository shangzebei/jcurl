/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.my.jcurl;

public class CurlUtilsJNI {
  public final static native long new_ParamMap__SWIG_0();
  public final static native long new_ParamMap__SWIG_1(long jarg1, ParamMap jarg1_);
  public final static native long ParamMap_size(long jarg1, ParamMap jarg1_);
  public final static native boolean ParamMap_empty(long jarg1, ParamMap jarg1_);
  public final static native void ParamMap_clear(long jarg1, ParamMap jarg1_);
  public final static native String ParamMap_get(long jarg1, ParamMap jarg1_, String jarg2);
  public final static native void ParamMap_set(long jarg1, ParamMap jarg1_, String jarg2, String jarg3);
  public final static native void ParamMap_del(long jarg1, ParamMap jarg1_, String jarg2);
  public final static native boolean ParamMap_has_key(long jarg1, ParamMap jarg1_, String jarg2);
  public final static native void delete_ParamMap(long jarg1);
  public final static native void Response_callback(long jarg1, Response jarg1_, int jarg2, String jarg3);
  public final static native void Response_callbackSwigExplicitResponse(long jarg1, Response jarg1_, int jarg2, String jarg3);
  public final static native long new_Response();
  public final static native void delete_Response(long jarg1);
  public final static native void Response_director_connect(Response obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void Response_change_ownership(Response obj, long cptr, boolean take_or_release);
  public final static native void ByteResponse_callback(long jarg1, ByteResponse jarg1_, int jarg2, java.nio.ByteBuffer jarg3, long jarg4);
  public final static native void ByteResponse_callbackSwigExplicitByteResponse(long jarg1, ByteResponse jarg1_, int jarg2, java.nio.ByteBuffer jarg3, long jarg4);
  public final static native long new_ByteResponse();
  public final static native void delete_ByteResponse(long jarg1);
  public final static native void ByteResponse_director_connect(ByteResponse obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void ByteResponse_change_ownership(ByteResponse obj, long cptr, boolean take_or_release);
  public final static native void Progress_progress(long jarg1, Progress jarg1_, long jarg2, long jarg3, long jarg4, long jarg5);
  public final static native void Progress_progressSwigExplicitProgress(long jarg1, Progress jarg1_, long jarg2, long jarg3, long jarg4, long jarg5);
  public final static native void Progress_setTag(long jarg1, Progress jarg1_, String jarg2);
  public final static native String Progress_getTag(long jarg1, Progress jarg1_);
  public final static native long new_Progress();
  public final static native void delete_Progress(long jarg1);
  public final static native void Progress_director_connect(Progress obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void Progress_change_ownership(Progress obj, long cptr, boolean take_or_release);
  public final static native long CurlUtil_get(String jarg1, long jarg2, Response jarg2_);
  public final static native long CurlUtil_deleteJ(String jarg1, long jarg2, Response jarg2_);
  public final static native long CurlUtil_put(String jarg1, long jarg2, Response jarg2_);
  public final static native long CurlUtil_post(String jarg1, long jarg2, Response jarg2_);
  public final static native long CurlUtil_getBytes(String jarg1, long jarg2, ByteResponse jarg2_);
  public final static native long CurlUtil_getFile(String jarg1, String jarg2);
  public final static native long CurlUtil_setProgress(long jarg1, CurlUtil jarg1_, long jarg2, Progress jarg2_);
  public final static native long CurlUtil_setParam(long jarg1, CurlUtil jarg1_, long jarg2, ParamMap jarg2_);
  public final static native long CurlUtil_setHeader(long jarg1, CurlUtil jarg1_, String jarg2);
  public final static native void CurlUtil_execute__SWIG_0(long jarg1, CurlUtil jarg1_, String jarg2);
  public final static native void CurlUtil_execute__SWIG_1(long jarg1, CurlUtil jarg1_);
  public final static native void CurlUtil_setTag(long jarg1, CurlUtil jarg1_, String jarg2);
  public final static native String CurlUtil_getTag(long jarg1, CurlUtil jarg1_);

  public static void SwigDirector_Response_callback(Response jself, int result, String s) {
    jself.callback(result, s);
  }
  public static void SwigDirector_ByteResponse_callback(ByteResponse jself, int result, java.nio.ByteBuffer buf, long len) {
    jself.callback(result, buf, len);
  }
  public static void SwigDirector_Progress_progress(Progress jself, long unow, long utotal, long dnow, long dtotal) {
    jself.progress(unow, utotal, dnow, dtotal);
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
