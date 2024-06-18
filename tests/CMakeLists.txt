include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/external/glfw/include" "${PROJECT_BINARY_DIR}/include/guilib/utilities")

set(UNIT_TEST_TARGETS image font label input-system push_button icon-button textbox drop-down checkbox radio-button)

add_executable(image image.cpp)
add_executable(font font.cpp)
add_executable(label label.cpp)
add_executable(input-system input_system.cpp)
add_executable(push_button push_button.cpp)
add_executable(icon-button icon_button.cpp)
add_executable(textbox textbox.cpp)
add_executable(drop-down drop_down.cpp)
add_executable(checkbox checkbox.cpp)
add_executable(radio-button radio_button.cpp)

foreach(TEST_TARGET IN LISTS UNIT_TEST_TARGETS)
    if (MSVC)
        target_link_options("${TEST_TARGET}" PRIVATE "/ENTRY:mainCRTStartup")
    endif()

    set_target_properties("${TEST_TARGET}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      FOLDER "LibUnitTests")

    target_link_libraries("${TEST_TARGET}" PRIVATE gui-library glfw)

    if (GUILIB_BUILD_SHARED)
        add_custom_command(TARGET "${TEST_TARGET}" POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy_if_different 
            "${CMAKE_BINARY_DIR}/bin/$<IF:$<CONFIG:Debug>,debug,release>/gui-library.dll" 
            "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>")
    endif()
endforeach()