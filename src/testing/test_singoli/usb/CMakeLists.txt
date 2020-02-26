cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( example )

include_directories(Comm)
set(SOURCES serial_test.cpp Comm/Braswell_comm.cpp)

add_executable( serial_test ${SOURCES} )

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
endif()
