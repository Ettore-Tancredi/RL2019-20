cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( main )
find_package( OpenCV REQUIRED )

include_directories(Parameters Debugging Constants Line Graphics Camera Image Log Lib Controller ${OpenCV_INCLUDE_DIRS} )
set(SOURCES Parameters/Parameters.cpp Debugging/Debugging.cpp Constants/Line_constants.cpp Image/Image.cpp Graphics/Graphics.cpp Camera/Camera.cpp Line/Line.cpp Line/Rig.cpp Log/Log.cpp main.cpp Lib/cv_types.h Controller/Controller.cpp)

add_executable( main ${SOURCES} )
target_link_libraries( main ${OpenCV_LIBS} )

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()
