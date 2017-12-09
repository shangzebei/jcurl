cmake_minimum_required(VERSION 3.6)
project(jcurl)

#add_subdirectory(src/main/cpp/Json/lib_json)

set(SWIG_SOURCE_FILE src/main/cpp/curljni.i)
SET(SWIG_CPP_OUT_FILE_NAME src/main/cpp/curljni.cxx)
SET(SWIG_JAVA_PACKAGE com.my.jcurl)
SET(SWIG_JAVA_OUT_DIR src/main/java/com/my/jcurl)
#/usr/local/opt/swig@3.04/bin/swig
execute_process(COMMAND /usr/local/opt/swig@3.04/bin/swig -c++ -outdir ${SWIG_JAVA_OUT_DIR} -o ${SWIG_CPP_OUT_FILE_NAME} -java -package ${SWIG_JAVA_PACKAGE} ${SWIG_SOURCE_FILE})#-o ${SWIG_CPP_OUT_FILE_NAME} -package ${SWIG_JAVA_PACKAGE}

set(SOURCE_FILES
        src/main/cpp/CurlUtil.cpp
        src/main/cpp/CurlUtil.h
        src/main/cpp/HttpClient.cpp
        src/main/cpp/HttpClient.h
        src/main/cpp/HttpCookie.cpp
        src/main/cpp/HttpCookie.h
        src/main/cpp/HttpRequest.h
        src/main/cpp/HttpResponse.h
        src/main/cpp/CAData.cpp
        src/main/cpp/CAData.h
        src/main/cpp/ccUtils.cpp
        src/main/cpp/ccUtils.h
        ${SWIG_CPP_OUT_FILE_NAME}
        )

add_library(curl STATIC IMPORTED)


set(curl_path ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/curl/prebuilt/android/${ANDROID_ABI}/libcurl.a)
set(curl_ssl ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/curl/prebuilt/android/${ANDROID_ABI}/libssl.a)
set(curl_crypto ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/curl/prebuilt/android/${ANDROID_ABI}/libcrypto.a)

set_target_properties(curl
  PROPERTIES IMPORTED_LOCATION
  ${curl_path})

INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS} src/main/cpp/curl/include/android/curl)

find_library(log_lib log)
find_library(z_lib z)
add_library(jcurl
         SHARED
        ${SOURCE_FILES}
)
message(warning ${z_lib})
target_link_libraries(jcurl ${log_lib} ${curl_path} ${curl_ssl} ${curl_crypto} ${z_lib})