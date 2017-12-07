/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package s.docker.com.jcurl;

public class Progress {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Progress(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Progress obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CurlUtilsJNI.delete_Progress(swigCPtr);
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
    CurlUtilsJNI.Progress_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    CurlUtilsJNI.Progress_change_ownership(this, swigCPtr, true);
  }

  public void progress(long unow, long utotal, long dnow, long dtotal) {
    if (getClass() == Progress.class) CurlUtilsJNI.Progress_progress(swigCPtr, this, unow, utotal, dnow, dtotal); else CurlUtilsJNI.Progress_progressSwigExplicitProgress(swigCPtr, this, unow, utotal, dnow, dtotal);
  }

  public Progress() {
    this(CurlUtilsJNI.new_Progress(), true);
    CurlUtilsJNI.Progress_director_connect(this, swigCPtr, swigCMemOwn, false);
  }

}
