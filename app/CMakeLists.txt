cmake_minimum_required(VERSION 3.6)
project(jcurl)
add_subdirectory(src/main/cpp/Json/lib_json)
#find_package(JNI)
set(SWIG_SOURCE_FILE src/main/cpp/curljni.i)
SET(SWIG_CPP_OUT_FILE_NAME src/main/cpp/curljni.c)
SET(SWIG_JAVA_OUT_DIR src/main/java/s/docker/com/jcurl)
SET(SWIG_JAVA_PACKAGE s.docker.com.jcurl)
execute_process(COMMAND swig -outdir ${SWIG_JAVA_OUT_DIR} -o ${SWIG_CPP_OUT_FILE_NAME} -java -package ${SWIG_JAVA_PACKAGE} ${SWIG_SOURCE_FILE})#-o ${SWIG_CPP_OUT_FILE_NAME} -package ${SWIG_JAVA_PACKAGE}
set(SOURCE_FILES
        src/main/cpp/CommonHttpManager.cpp
        src/main/cpp/CommonHttpManager.h
        src/main/cpp/HttpClient.cpp
        src/main/cpp/HttpClient.h
        src/main/cpp/HttpCookie.cpp
        src/main/cpp/HttpCookie.h
        src/main/cpp/HttpRequest.h
        src/main/cpp/HttpResponse.h
        src/main/cpp/CAData.cpp
        src/main/cpp/CAData.h
        src/main/cpp/native-lib.cpp
        ${SWIG_CPP_OUT_FILE_NAME}
        )
set(curl_path ${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp/curl/prebuilt/android/${ANDROID_ABI})
INCLUDE_DIRECTORIES(${JNI_INCLUDE_DIRS} src/main/cpp/curl/include/android/curl src/main/cpp/Json/lib_json)
find_library(log_lib log)
add_library(
        jcurl ${SOURCE_FILES}
)
target_link_libraries(jcurl ${log_lib} ${lib_json} ${curl_path})