#add_library(curl
#  prebuilt/android/armeabi/libcurl.a
#)
#target_link_libraries(curl prebuilt/android/armeabi/libcrypto.a prebuilt/android/armeabi/libssl.a)
#add_library(curl STATIC IMPORTED)
#set(curl_path ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/curl/prebuilt/android/${ANDROID_ABI}/libcurl.a)
#set_target_properties(curl
#  PROPERTIES IMPORTED_LOCATION
#  ${curl_path})