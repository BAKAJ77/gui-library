#ifndef GUILIB_H
#define GUILIB_H

#include <components/interface_frame.h>
#include <utilities/libexport.h>
#include <external/glad/glad.h>

struct GLFWwindow;

namespace GUILib
{
	/**
	* @brief Initializes the GLFW implementation version of this GUI library.
	* It is required to initialize this GUI library before using any of its provided features.
	* 
	* @param[in] window - A pointer to a created GLFW window instance.
	* @param[in] loadProcFunc - The function this library will use to load the necessary OpenGL functions.
	* @return TRUE if the operation was a success, else FALSE is returned indicating failure.
	*/
	LIB_DECLSPEC extern bool InitLibraryGLFWImpl(GLFWwindow* window, GLADloadproc loadProcFunc);

	/**
	* @brief De-initializes the GUI library by freeing up allocations made by the library, this should be called before destroying the OpenGL
	* context.
	* Note that any allocations you have made which is not tracked by the resource manager need to deleted manually,
	* it is recommended to do this before destroying the OpenGL context since most of the classes provided by this library rely on OpenGL.
	*/
	LIB_DECLSPEC extern void FreeLibrary();
}

#endif
