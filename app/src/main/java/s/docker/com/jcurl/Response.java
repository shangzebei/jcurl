/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package s.docker.com.jcurl;

public class Response {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected Response(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Response obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CurlUtilsJNI.delete_Response(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void callback(int result, String s) {
    CurlUtilsJNI.Response_callback(swigCPtr, this, result, s);
  }

  public Response() {
    this(CurlUtilsJNI.new_Response(), true);
  }

}
