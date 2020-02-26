cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( test )
find_package( OpenCV REQUIRED )

include_directories(Camera ${OpenCV_INCLUDE_DIRS})
set(SOURCES camera_test.cpp Camera/Camera.cpp)

add_executable( camera_test ${SOURCES} )
target_link_libraries( camera_test ${OpenCV_LIBS} )
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()



