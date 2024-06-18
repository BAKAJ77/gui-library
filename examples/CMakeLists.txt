include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/external/glfw/include" "${PROJECT_BINARY_DIR}/include/guilib/utilities")

set(EXAMPLES login-form)

add_executable(login-form login_form.cpp)

foreach(EXAMPLE IN LISTS EXAMPLES)
    if (MSVC)
        target_link_options("${EXAMPLE}" PRIVATE "/ENTRY:mainCRTStartup")
    endif()

    set_target_properties("${EXAMPLE}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples/$<IF:$<CONFIG:Debug>,debug,release>"
                                                      FOLDER "Examples")

    target_link_libraries("${EXAMPLE}" PRIVATE gui-library glfw)

    if (GUILIB_BUILD_SHARED)
        add_custom_command(TARGET "${EXAMPLE}" POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy_if_different 
            "${CMAKE_BINARY_DIR}/bin/$<IF:$<CONFIG:Debug>,debug,release>/gui-library.dll" 
            "${CMAKE_BINARY_DIR}/bin/examples/$<IF:$<CONFIG:Debug>,debug,release>")
    endif()
endforeach()