cmake_minimum_required(VERSION 4.0)
project(PackReaderTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(PackReader STATIC IMPORTED)
set_target_properties(PackReader PROPERTIES
    IMPORTED_LOCATION "F:/Projects/Cpp/Tools/Resource-Management-Tools/PackReader/build/Debug/PackReader.lib"
    INTERFACE_INCLUDE_DIRECTORIES "F:/Projects/Cpp/Tools/Resource-Management-Tools/PackReader/inc"
)

add_executable(${PROJECT_NAME} src/reader_test.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC PackReader)