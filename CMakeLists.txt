cmake_minimum_required(VERSION 3.10)
project(x11pp LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11  -fpermissive -Wno-deprecated-declarations -Wno-deprecated -Wno-conversion-null")

add_library(${PROJECT_NAME} SHARED src/${PROJECT_NAME}.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE X11 Xrandr xcb)

add_executable(${PROJECT_NAME}_test src/${PROJECT_NAME}_test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
