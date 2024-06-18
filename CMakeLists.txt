cmake_minimum_required(VERSION 3.24.1)
project(gui-library VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(LIB_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include/guilib" "${PROJECT_SOURCE_DIR}/external/glfw/include")

set(LIB_COMPONENTS_SRC_FILES "include/guilib/components/component.h" "include/guilib/components/component.cpp" "include/guilib/components/interface_frame.h" 
    "include/guilib/components/interface_frame.cpp" "include/guilib/components/image.h" "include/guilib/components/image.cpp" 
    "include/guilib/components/label.h" "include/guilib/components/label.cpp" "include/guilib/components/button.h" "include/guilib/components/button.cpp" 
    "include/guilib/components/icon_button.h" "include/guilib/components/icon_button.cpp" "include/guilib/components/push_button.h" 
    "include/guilib/components/push_button.cpp" "include/guilib/components/textbox.h" "include/guilib/components/textbox.cpp" 
    "include/guilib/components/focusable_component.h" "include/guilib/components/focusable_component.cpp" "include/guilib/components/drop_down.h"
    "include/guilib/components/drop_down.cpp" "include/guilib/components/checkbox.h" "include/guilib/components/checkbox.cpp"
    "include/guilib/components/radio_button.h" "include/guilib/components/radio_button.cpp" "include/guilib/components/radio_group.h" 
    "include/guilib/components/radio_group.cpp")

set(LIB_EXTERNAL_SRC_FILES "include/guilib/external/glad/glad.h"  "include/guilib/external/glad/glad.c" "include/guilib/external/KHR/khrplatform.h"
    "include/guilib/external/stb_image.cpp")

set(LIB_GRAPHICS_SRC_FILES "include/guilib/graphics/buffer_objects.h" "include/guilib/graphics/buffer_objects.cpp" "include/guilib/graphics/vertex_array.h"
    "include/guilib/graphics/vertex_array.cpp" "include/guilib/graphics/shader_program.h" "include/guilib/graphics/shader_program.cpp"
    "include/guilib/graphics/font.h" "include/guilib/graphics/font.cpp" "include/guilib/graphics/viewport.h" "include/guilib/graphics/viewport.cpp"
    "include/guilib/graphics/animation.h")

set(LIB_UTILITIES_SRC_FILES "include/guilib/utilities/libexport.h" "include/guilib/utilities/resource_loader.h" 
    "include/guilib/utilities/resource_loader.cpp" "include/guilib/utilities/input_system.h" "include/guilib/utilities/input_system.cpp"
    "include/guilib/utilities/timer.h" "include/guilib/utilities/timer.cpp")

set(BUILD_SHARED_LIBS OFF) # Force GLFW and FreeType libraries to built as static libs
option(GUILIB_BUILD_SHARED "Build the GUI library as a shared library" ON)

if (GUILIB_BUILD_SHARED)
    add_library(gui-library SHARED "${LIB_COMPONENTS_SRC_FILES}" "${LIB_EXTERNAL_SRC_FILES}" "${LIB_GRAPHICS_SRC_FILES}" "${LIB_UTILITIES_SRC_FILES}"
        "include/guilib/guilib.h" "include/guilib/guilib.cpp")
else()
    add_library(gui-library STATIC "${LIB_COMPONENTS_SRC_FILES}" "${LIB_EXTERNAL_SRC_FILES}" "${LIB_GRAPHICS_SRC_FILES}" "${LIB_UTILITIES_SRC_FILES}")
endif()

target_include_directories(gui-library PUBLIC "${LIB_INCLUDE_DIRECTORIES}")
set_target_properties(gui-library PROPERTIES RUNTIME_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>"
                                             LIBRARY_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>"
                                             ARCHIVE_OUTPUT_DIRECTORY "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/debug,${CMAKE_BINARY_DIR}/bin/release>")

add_subdirectory(include/guilib/external/freetype)
add_subdirectory(external/glfw)

target_link_libraries(gui-library PRIVATE freetype glfw)

if (MSVC)
    target_compile_options(gui-library PRIVATE "/std:c++17")
    target_link_options(gui-library PRIVATE "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS>")
endif()

if (GUILIB_BUILD_SHARED)
    target_compile_definitions(gui-library PRIVATE "LIB_EXPORT_DLL")
else()
    target_compile_definitions(gui-library PRIVATE "LIB_STATIC")
endif()

configure_file("include/guilib/utilities/assets_path.h.in" "include/guilib/utilities/assets_path.h")

add_subdirectory(tests)
add_subdirectory(examples)