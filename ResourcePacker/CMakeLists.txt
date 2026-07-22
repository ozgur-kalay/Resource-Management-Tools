cmake_minimum_required(VERSION 4.0)
project(ResourcePacker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Packages and Libraries

# wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

add_library(ResPackingCommon STATIC IMPORTED)
set_target_properties(ResPackingCommon PROPERTIES
    IMPORTED_LOCATION "F:/Projects/Cpp/Tools/Resource-Management-Tools/ResPackingCommon/build/Debug/ResPackingCommon.lib"
    INTERFACE_INCLUDE_DIRECTORIES "F:/Projects/Cpp/Tools/Resource-Management-Tools/ResPackingCommon/inc"
)

include(${wxWidgets_USE_FILE})

# Event system
add_subdirectory(third_party/EventSystem)

add_executable(${PROJECT_NAME} WIN32 
    # App
    src/app.cpp
    src/main_frame.cpp

    # Controls
    src/controls/main_panel.cpp
    src/controls/packing_choices_controls.cpp
    src/controls/pack_file_name_controls.cpp
    src/controls/output_dir_controls.cpp
    src/controls/access_name_choices_controls.cpp
    src/controls/res_table_buttons_controls.cpp
    src/controls/res_table_controls.cpp

    
    src/packing/pack_manager.cpp
    src/packing/pack_maker.cpp
    src/packing/resource_file_entry.cpp
)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} EventSystem ResPackingCommon)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header_files)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)
