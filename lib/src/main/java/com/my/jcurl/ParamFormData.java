/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.my.jcurl;

public class ParamFormData {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ParamFormData(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ParamFormData obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        CurlUtilsJNI.delete_ParamFormData(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setName(String value) {
    CurlUtilsJNI.ParamFormData_name_set(swigCPtr, this, value);
  }

  public String getName() {
    return CurlUtilsJNI.ParamFormData_name_get(swigCPtr, this);
  }

  public void setFiles(ParamArray value) {
    CurlUtilsJNI.ParamFormData_files_set(swigCPtr, this, ParamArray.getCPtr(value), value);
  }

  public ParamArray getFiles() {
    long cPtr = CurlUtilsJNI.ParamFormData_files_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ParamArray(cPtr, false);
  }

  public void setValue(String value) {
    CurlUtilsJNI.ParamFormData_value_set(swigCPtr, this, value);
  }

  public String getValue() {
    return CurlUtilsJNI.ParamFormData_value_get(swigCPtr, this);
  }

  public void setType(ParamFormData.Type value) {
    CurlUtilsJNI.ParamFormData_type_set(swigCPtr, this, value.swigValue());
  }

  public ParamFormData.Type getType() {
    return ParamFormData.Type.swigToEnum(CurlUtilsJNI.ParamFormData_type_get(swigCPtr, this));
  }

  public ParamFormData() {
    this(CurlUtilsJNI.new_ParamFormData(), true);
  }

  public final static class Type {
    public final static ParamFormData.Type TEXT = new ParamFormData.Type("TEXT", CurlUtilsJNI.ParamFormData_Type_TEXT_get());
    public final static ParamFormData.Type FILE = new ParamFormData.Type("FILE");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static Type swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + Type.class + " with value " + swigValue);
    }

    private Type(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private Type(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private Type(String swigName, Type swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static Type[] swigValues = { TEXT, FILE };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
