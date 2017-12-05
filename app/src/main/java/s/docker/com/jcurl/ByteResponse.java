/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package s.docker.com.jcurl;

public class ByteResponse {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ByteResponse(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ByteResponse obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CurlUtilsJNI.delete_ByteResponse(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    CurlUtilsJNI.ByteResponse_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    CurlUtilsJNI.ByteResponse_change_ownership(this, swigCPtr, true);
  }

  public void callback(int result, java.nio.ByteBuffer buf, long len) {
  assert buf.isDirect() : "Buffer must be allocated direct.";
    {
      if (getClass() == ByteResponse.class) CurlUtilsJNI.ByteResponse_callback(swigCPtr, this, result, buf, len); else CurlUtilsJNI.ByteResponse_callbackSwigExplicitByteResponse(swigCPtr, this, result, buf, len);
    }
  }

  public ByteResponse() {
    this(CurlUtilsJNI.new_ByteResponse(), true);
    CurlUtilsJNI.ByteResponse_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
