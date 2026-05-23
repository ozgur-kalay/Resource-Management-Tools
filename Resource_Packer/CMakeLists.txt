cmake_minimum_required(VERSION 3.28)

project(ResourcePacker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

file(GLOB_RECURSE GUI_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GUI/src/*.cpp"
)

add_executable(ResourcePacker
    src/main.cpp

    ${GUI_SOURCE_FILES}

    app.rc
)

target_include_directories(${PROJECT_NAME} PRIVATE src/GUI/Include)

target_link_libraries(ResourcePacker PRIVATE ${wxWidgets_LIBRARIES})