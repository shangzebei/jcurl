/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package s.docker.com.jcurl;

public class CurlUtils {
  public static void setCurlUtil(CurlUtil value) {
    CurlUtilsJNI.curlUtil_set(CurlUtil.getCPtr(value), value);
  }

  public static CurlUtil getCurlUtil() {
    long cPtr = CurlUtilsJNI.curlUtil_get();
    return (cPtr == 0) ? null : new CurlUtil(cPtr, false);
  }

}
