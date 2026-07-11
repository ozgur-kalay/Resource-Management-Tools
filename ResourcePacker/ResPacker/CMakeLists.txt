cmake_minimum_required(VERSION 4.0)
project(ResourcePacker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_subdirectory(vendor/EventSystem)

add_executable(${PROJECT_NAME} WIN32 
    # App
    src/app.cpp
    src/main_frame.cpp

    # Controls
    src/controls/main_panel.cpp
    src/controls/packing_choices_controls.cpp
    src/controls/pack_file_name_controls.cpp
    src/controls/output_dir_controls.cpp
    src/controls/res_access_path_choices_controls.cpp
    src/controls/res_table_buttons_controls.cpp
    src/controls/res_table_controls.cpp

)


target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} EventSystem)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header_files)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)

