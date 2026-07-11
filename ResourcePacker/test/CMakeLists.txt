cmake_minimum_required(VERSION 4.0)
project(ResourcePackerTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(raylib STATIC IMPORTED)
set_target_properties(
    raylib PROPERTIES
    IMPORTED_LOCATION_DEBUG "F:/Engines/raylib/build_a/raylib/Debug/libraylib.a"
    IMPORTED_LOCATION_RELEASE "F:/Engines/raylib/build_a/raylib/Release/libraylib.a"
    IMPORTED_CONFIGURATIONS "DEBUG;RELEASE"
    INTERFACE_INCLUDE_DIRECTORIES "F:/Engines/raylib/build_a/raylib/include"
    INTERFACE_LINK_LIBRARIES "winmm"
)

add_executable(${PROJECT_NAME} src/test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)