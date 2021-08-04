PROJECT(WindowMgr)

cmake_minimum_required(VERSION 3.10)


file(GLOB SOURCES
     "include/*.h"
     "src/*.cpp")


include_directories(.)
include_directories(./include/)

set(WINDOWMANAGER_TARGET "WindowMgr")

set(GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS}  -std=c++11  -fpermissive -Wno-deprecated-declarations -Wno-deprecated -Wno-conversion-null")

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

add_executable(${WINDOWMANAGER_TARGET} ${SOURCES})


target_link_libraries(${WINDOWMANAGER_TARGET} X11 Xrandr xcb)