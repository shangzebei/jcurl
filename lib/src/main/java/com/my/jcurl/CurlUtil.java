/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.my.jcurl;

public class CurlUtil {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected CurlUtil(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(CurlUtil obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        throw new UnsupportedOperationException("C++ destructor does not have public access");
      }
      swigCPtr = 0;
    }
  }

  public static CurlUtil get(String url, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_get(url, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil deleteJ(String url, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_deleteJ(url, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil put(String url, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_put(url, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil post(String url, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_post(url, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil getBytes(String url, ByteResponse response) {
    long cPtr = CurlUtilsJNI.CurlUtil_getBytes(url, ByteResponse.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil getFile(String url, String toPath) {
    long cPtr = CurlUtilsJNI.CurlUtil_getFile(url, toPath);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil postFormData(String url, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_postFormData(url, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil uploadMultiFile(String url, ParamMap key_file, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_uploadMultiFile__SWIG_0(url, ParamMap.getCPtr(key_file), key_file, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public static CurlUtil uploadMultiFile(String url, ParamFormMap key_file, Response response) {
    long cPtr = CurlUtilsJNI.CurlUtil_uploadMultiFile__SWIG_1(url, ParamFormMap.getCPtr(key_file), key_file, Response.getCPtr(response), response);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public CurlUtil setProgress(Progress progress) {
    long cPtr = CurlUtilsJNI.CurlUtil_setProgress(swigCPtr, this, Progress.getCPtr(progress), progress);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public CurlUtil setParam(ParamMap key_value) {
    long cPtr = CurlUtilsJNI.CurlUtil_setParam(swigCPtr, this, ParamMap.getCPtr(key_value), key_value);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public CurlUtil setParamData(String data) {
    long cPtr = CurlUtilsJNI.CurlUtil_setParamData(swigCPtr, this, data);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public CurlUtil setHeader(String header) {
    long cPtr = CurlUtilsJNI.CurlUtil_setHeader(swigCPtr, this, header);
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

  public void execute(String tag) {
    CurlUtilsJNI.CurlUtil_execute__SWIG_0(swigCPtr, this, tag);
  }

  public void execute() {
    CurlUtilsJNI.CurlUtil_execute__SWIG_1(swigCPtr, this);
  }

  public void setTag(String tag) {
    CurlUtilsJNI.CurlUtil_setTag(swigCPtr, this, tag);
  }

  public String getTag() {
    return CurlUtilsJNI.CurlUtil_getTag(swigCPtr, this);
  }

}
