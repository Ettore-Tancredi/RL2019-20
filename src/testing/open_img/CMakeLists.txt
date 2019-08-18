cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( cv_test )
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


set(SOURCES open_img.cpp)

add_executable( cv_test ${SOURCES} )
target_link_libraries( cv_test ${OpenCV_LIBS} )