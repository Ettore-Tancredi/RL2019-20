cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( main )
find_package( OpenCV REQUIRED )


include_directories(Line graphics camera Image Log Lib ${OpenCV_INCLUDE_DIRS} )
set(SOURCES Image/Image.cpp Graphics/Graphics.cpp Camera/Camera.cpp Line/Line.cpp Line/Rig.cpp Log/Log.cpp main.cpp Lib/types.h Lib/rmath.h)



add_executable( main ${SOURCES} )
target_link_libraries( main ${OpenCV_LIBS} )