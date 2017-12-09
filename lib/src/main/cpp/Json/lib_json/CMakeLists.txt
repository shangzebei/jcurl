file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        )
add_library(lib_json ${SOURCE_FILES})