cmake_minimum_required(VERSION 4.0)
project(PackReader)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ResPackingCommon STATIC IMPORTED)
set_target_properties(ResPackingCommon PROPERTIES
    IMPORTED_LOCATION "F:/Projects/Cpp/Tools/Resource-Management-Tools/ResPackingCommon/build/Debug/ResPackingCommon.lib"
    INTERFACE_INCLUDE_DIRECTORIES "F:/Projects/Cpp/Tools/Resource-Management-Tools/ResPackingCommon/inc"
)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pack_reader.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC ResPackingCommon)

