#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <utilities/libexport.h>
#include <graphics/viewport.h>
#include <external/glm/glm/glm.hpp>

struct GLFWwindow;

namespace GUILib
{
	/**
	* @brief An enumeration representing input key codes.
	*/
	enum class KeyCode
	{
		// Printable Keys
		KEY_SPACE,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUAL,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACKET, // [
		KEY_BACKSLASH,
		KEY_RIGHT_BRACKET, // ]
		KEY_GRAVE_ACCENT,
		KEY_WORLD_1,
		KEY_WORLD_2,

		// Function Keys
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPS_LOCK,
		KEY_SCROLL_LOCK,
		KEY_NUM_LOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_F25,
		KEY_KP_0,
		KEY_KP_1,
		KEY_KP_2,
		KEY_KP_3,
		KEY_KP_4,
		KEY_KP_5,
		KEY_KP_6,
		KEY_KP_7,
		KEY_KP_8,
		KEY_KP_9,
		KEY_KP_DECIMAL,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_SUBTRACT,
		KEY_KP_ADD,
		KEY_KP_ENTER,
		KEY_KP_EQUAL,
		KEY_LEFT_SHIFT,
		KEY_LEFT_CONTROL,
		KEY_LEFT_ALT,
		KEY_LEFT_SUPER,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_ALT,
		KEY_RIGHT_SUPER,
		KEY_MENU,
		KEY_LAST
	};

	/**
	* @brief An enumeration representing input mouse button codes.
	*/
	enum class MouseButtonCode
	{
		MOUSE_BUTTON_1,
		MOUSE_BUTTON_2,
		MOUSE_BUTTON_3,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,
		MOUSE_BUTTON_LAST,
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE
	};

	class LIB_DECLSPEC InputSystem
	{
	public:
		~InputSystem() = default;

		/**
		* @brief Initializes the GLFW implementation of the input system.
		* This is automatically called by the GUILib::InitLibraryGLFWImpl() function.
		* 
		* @param[in] window - A pointer to a created GLFW window instance.
		*/
		void InitGLFWImpl(GLFWwindow* window);

		/**
		* @brief Checks whether or not the specified key was pressed.
		* 
		* @param[in] key - The key to be looked up.
		* @return TRUE if the key pressed, FALSE otherwise.
		*/
		bool WasKeyPressed(KeyCode key) const;

		/**
		* @brief Checks whether or not the specified mouse button was pressed.
		*
		* @param[in] button - The mouse button to be looked up.
		* @return TRUE if the mouse button pressed, FALSE otherwise.
		*/
		bool WasMouseButtonPressed(MouseButtonCode button) const;

		/**
		* @brief Retrieves the current position of the mouse cursor.
		* By default, the retrieved coordinates will be relative to the window, however if you provide a viewport then the cursor position will 
		* be mapped to the viewport's coordinates.
		* 
		* @param[in] viewport - The viewport to map the cursor position to (this is an optional paramter).
		* @return A 2-dimensional vector representing the current position of the cursor.
		*/
		glm::vec2 GetCursorPosition(const Viewport* viewport = nullptr) const;

		/**
		* @brief Retrieves the offset the user scrolled using their mouse/touchpad.
		* @return A 2 dimensional vector representing the offset scrolled (vertically and/or horizontally) by the mouse/touchpad.
		*/
		glm::vec2 GetScrollOffset() const;

		/**
		* @brief Returns the unicode value of the next pending inputted text character.
		* @return Unicode value of the next pending inputted text character, if no characters are pending then 0 is returned.
		*/
		uint32_t GetInputtedCharacter() const;

		static InputSystem& GetInstance();
	private:
		InputSystem() = default;

		int GetGLFWKeyCode(KeyCode key) const;
		int GetGLFWMouseCode(MouseButtonCode button) const;
	private:
		GLFWwindow* m_glfwWindow;
	};
}

#endif