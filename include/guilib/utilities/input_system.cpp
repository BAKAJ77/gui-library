#include <utilities/input_system.h>
#include <GLFW/glfw3.h>

namespace GUILib
{
	namespace Callbacks
	{
		static uint32_t characterInputted = 0x0;
		static void PollTextInputCallback(GLFWwindow* window, uint32_t codePoint)
		{
			characterInputted = codePoint;
		}

		static glm::vec2 scrollOffset;
		static void GetScrollOffsetsCallback(GLFWwindow* window, double offsetX, double offsetY)
		{
			scrollOffset = { (float)offsetX, (float)offsetY };
		}
	}

	void InputSystem::InitGLFWImpl(GLFWwindow* window) 
	{ 
		m_glfwWindow = window; 

		// Setup the callback functions
		glfwSetCharCallback(window, Callbacks::PollTextInputCallback);
		glfwSetScrollCallback(window, Callbacks::GetScrollOffsetsCallback);
	}

	int InputSystem::GetGLFWKeyCode(KeyCode key) const
	{
		switch (key)
		{
			case KeyCode::KEY_SPACE: return GLFW_KEY_SPACE;
			case KeyCode::KEY_APOSTROPHE: return GLFW_KEY_APOSTROPHE;
			case KeyCode::KEY_COMMA: return GLFW_KEY_COMMA;
			case KeyCode::KEY_MINUS: return GLFW_KEY_MINUS;
			case KeyCode::KEY_PERIOD: return GLFW_KEY_PERIOD;
			case KeyCode::KEY_SLASH: return GLFW_KEY_SLASH;
			case KeyCode::KEY_0: return GLFW_KEY_0;
			case KeyCode::KEY_1: return GLFW_KEY_1;
			case KeyCode::KEY_2: return GLFW_KEY_2;
			case KeyCode::KEY_3: return GLFW_KEY_3;
			case KeyCode::KEY_4: return GLFW_KEY_4;
			case KeyCode::KEY_5: return GLFW_KEY_5;
			case KeyCode::KEY_6: return GLFW_KEY_6;
			case KeyCode::KEY_7: return GLFW_KEY_7;
			case KeyCode::KEY_8: return GLFW_KEY_8;
			case KeyCode::KEY_9: return GLFW_KEY_9;
			case KeyCode::KEY_SEMICOLON: return GLFW_KEY_SEMICOLON;
			case KeyCode::KEY_EQUAL: return GLFW_KEY_EQUAL;
			case KeyCode::KEY_A: return GLFW_KEY_A;
			case KeyCode::KEY_B: return GLFW_KEY_B;
			case KeyCode::KEY_C: return GLFW_KEY_C;
			case KeyCode::KEY_D: return GLFW_KEY_D;
			case KeyCode::KEY_E: return GLFW_KEY_E;
			case KeyCode::KEY_F: return GLFW_KEY_F;
			case KeyCode::KEY_G: return GLFW_KEY_G;
			case KeyCode::KEY_H: return GLFW_KEY_H;
			case KeyCode::KEY_I: return GLFW_KEY_I;
			case KeyCode::KEY_J: return GLFW_KEY_J;
			case KeyCode::KEY_K: return GLFW_KEY_K;
			case KeyCode::KEY_L: return GLFW_KEY_L;
			case KeyCode::KEY_M: return GLFW_KEY_M;
			case KeyCode::KEY_N: return GLFW_KEY_N;
			case KeyCode::KEY_O: return GLFW_KEY_O;
			case KeyCode::KEY_P: return GLFW_KEY_P;
			case KeyCode::KEY_Q: return GLFW_KEY_Q;
			case KeyCode::KEY_R: return GLFW_KEY_R;
			case KeyCode::KEY_S: return GLFW_KEY_S;
			case KeyCode::KEY_T: return GLFW_KEY_T;
			case KeyCode::KEY_U: return GLFW_KEY_U;
			case KeyCode::KEY_V: return GLFW_KEY_V;
			case KeyCode::KEY_W: return GLFW_KEY_W;
			case KeyCode::KEY_X: return GLFW_KEY_X;
			case KeyCode::KEY_Y: return GLFW_KEY_Y;
			case KeyCode::KEY_Z: return GLFW_KEY_Z;
			case KeyCode::KEY_LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET; // [
			case KeyCode::KEY_BACKSLASH: return GLFW_KEY_BACKSLASH;
			case KeyCode::KEY_RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET; // ]
			case KeyCode::KEY_GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
			case KeyCode::KEY_WORLD_1: return GLFW_KEY_WORLD_1;
			case KeyCode::KEY_WORLD_2: return GLFW_KEY_WORLD_2;
			case KeyCode::KEY_ESCAPE: return GLFW_KEY_ESCAPE;
			case KeyCode::KEY_ENTER: return GLFW_KEY_ENTER;
			case KeyCode::KEY_TAB: return GLFW_KEY_TAB;
			case KeyCode::KEY_BACKSPACE: return GLFW_KEY_BACKSPACE;
			case KeyCode::KEY_INSERT: return GLFW_KEY_INSERT;
			case KeyCode::KEY_DELETE: return GLFW_KEY_DELETE;
			case KeyCode::KEY_RIGHT: return GLFW_KEY_RIGHT;
			case KeyCode::KEY_LEFT: return GLFW_KEY_LEFT;
			case KeyCode::KEY_DOWN: return GLFW_KEY_DOWN;
			case KeyCode::KEY_UP: return GLFW_KEY_UP;
			case KeyCode::KEY_PAGE_UP: return GLFW_KEY_PAGE_UP;
			case KeyCode::KEY_PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
			case KeyCode::KEY_HOME: return GLFW_KEY_HOME;
			case KeyCode::KEY_END: return GLFW_KEY_END;
			case KeyCode::KEY_CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
			case KeyCode::KEY_SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
			case KeyCode::KEY_NUM_LOCK: return GLFW_KEY_NUM_LOCK;
			case KeyCode::KEY_PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
			case KeyCode::KEY_PAUSE: return GLFW_KEY_PAUSE;
			case KeyCode::KEY_F1: return GLFW_KEY_F1;
			case KeyCode::KEY_F2: return GLFW_KEY_F2;
			case KeyCode::KEY_F3: return GLFW_KEY_F3;
			case KeyCode::KEY_F4: return GLFW_KEY_F4;
			case KeyCode::KEY_F5: return GLFW_KEY_F5;
			case KeyCode::KEY_F6: return GLFW_KEY_F6;
			case KeyCode::KEY_F7: return GLFW_KEY_F7;
			case KeyCode::KEY_F8: return GLFW_KEY_F8;
			case KeyCode::KEY_F9: return GLFW_KEY_F9;
			case KeyCode::KEY_F10: return GLFW_KEY_F10;
			case KeyCode::KEY_F11: return GLFW_KEY_F11;
			case KeyCode::KEY_F12: return GLFW_KEY_F12;
			case KeyCode::KEY_F13: return GLFW_KEY_F13;
			case KeyCode::KEY_F14: return GLFW_KEY_F14;
			case KeyCode::KEY_F15: return GLFW_KEY_F15;
			case KeyCode::KEY_F16: return GLFW_KEY_F16;
			case KeyCode::KEY_F17: return GLFW_KEY_F17;
			case KeyCode::KEY_F18: return GLFW_KEY_F18;
			case KeyCode::KEY_F19: return GLFW_KEY_F19;
			case KeyCode::KEY_F20: return GLFW_KEY_F20;
			case KeyCode::KEY_F21: return GLFW_KEY_F21;
			case KeyCode::KEY_F22: return GLFW_KEY_F22;
			case KeyCode::KEY_F23: return GLFW_KEY_F23;
			case KeyCode::KEY_F24: return GLFW_KEY_F24;
			case KeyCode::KEY_F25: return GLFW_KEY_F25;
			case KeyCode::KEY_KP_0: return GLFW_KEY_KP_0;
			case KeyCode::KEY_KP_1: return GLFW_KEY_KP_1;
			case KeyCode::KEY_KP_2: return GLFW_KEY_KP_2;
			case KeyCode::KEY_KP_3: return GLFW_KEY_KP_3;
			case KeyCode::KEY_KP_4: return GLFW_KEY_KP_4;
			case KeyCode::KEY_KP_5: return GLFW_KEY_KP_5;
			case KeyCode::KEY_KP_6: return GLFW_KEY_KP_6;
			case KeyCode::KEY_KP_7: return GLFW_KEY_KP_7;
			case KeyCode::KEY_KP_8: return GLFW_KEY_KP_8;
			case KeyCode::KEY_KP_9: return GLFW_KEY_KP_9;
			case KeyCode::KEY_KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
			case KeyCode::KEY_KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
			case KeyCode::KEY_KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
			case KeyCode::KEY_KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
			case KeyCode::KEY_KP_ADD: return GLFW_KEY_KP_ADD;
			case KeyCode::KEY_KP_ENTER: return GLFW_KEY_KP_ENTER;
			case KeyCode::KEY_KP_EQUAL: return GLFW_KEY_KP_EQUAL;
			case KeyCode::KEY_LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
			case KeyCode::KEY_LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
			case KeyCode::KEY_LEFT_ALT: return GLFW_KEY_LEFT_ALT;
			case KeyCode::KEY_LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
			case KeyCode::KEY_RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
			case KeyCode::KEY_RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
			case KeyCode::KEY_RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
			case KeyCode::KEY_RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
			case KeyCode::KEY_MENU: return GLFW_KEY_MENU;
			case KeyCode::KEY_LAST: return GLFW_KEY_MENU;
		}

		return -1;
	}

	int InputSystem::GetGLFWMouseCode(MouseButtonCode button) const
	{
		switch (button)
		{
			case MouseButtonCode::MOUSE_BUTTON_1: return GLFW_MOUSE_BUTTON_1;
			case MouseButtonCode::MOUSE_BUTTON_2: return GLFW_MOUSE_BUTTON_2;
			case MouseButtonCode::MOUSE_BUTTON_3: return GLFW_MOUSE_BUTTON_3;
			case MouseButtonCode::MOUSE_BUTTON_4: return GLFW_MOUSE_BUTTON_4;
			case MouseButtonCode::MOUSE_BUTTON_5: return GLFW_MOUSE_BUTTON_5;
			case MouseButtonCode::MOUSE_BUTTON_6: return GLFW_MOUSE_BUTTON_6;
			case MouseButtonCode::MOUSE_BUTTON_7: return GLFW_MOUSE_BUTTON_7;
			case MouseButtonCode::MOUSE_BUTTON_8: return GLFW_MOUSE_BUTTON_8;
			case MouseButtonCode::MOUSE_BUTTON_LAST: return GLFW_MOUSE_BUTTON_8;
			case MouseButtonCode::MOUSE_BUTTON_LEFT: return GLFW_MOUSE_BUTTON_1;
			case MouseButtonCode::MOUSE_BUTTON_RIGHT: return GLFW_MOUSE_BUTTON_2;
			case MouseButtonCode::MOUSE_BUTTON_MIDDLE: return GLFW_MOUSE_BUTTON_3;
		}

		return -1;
	}

	bool InputSystem::WasKeyPressed(KeyCode key) const
	{
		return glfwGetKey(m_glfwWindow, this->GetGLFWKeyCode(key));
	}

	bool InputSystem::WasMouseButtonPressed(MouseButtonCode button) const
	{
		return glfwGetMouseButton(m_glfwWindow, this->GetGLFWMouseCode(button));
	}

	glm::vec2 InputSystem::GetCursorPosition(const Viewport* viewport) const
	{
		// Get the current cursor position
		double cursorPosX = 0.0, cursorPosY = 0.0;
		glfwGetCursorPos(m_glfwWindow, &cursorPosX, &cursorPosY);

		// If a viewport camera was given then map the cursor position to it's dimensions
		if (viewport)
		{
			int windowWidth = 0, windowHeight = 0;
			glfwGetWindowSize(m_glfwWindow, &windowWidth, &windowHeight);
			cursorPosX = viewport->GetPosition().x + (cursorPosX * (viewport->GetSize().x / (float)windowWidth));
			cursorPosY = viewport->GetPosition().y + (cursorPosY * (viewport->GetSize().y / (float)windowHeight));
		}

		return glm::vec2((float)cursorPosX, (float)cursorPosY);
	}

	glm::vec2 InputSystem::GetScrollOffset() const
	{
		const glm::vec2 scrollOffset = Callbacks::scrollOffset;
		Callbacks::scrollOffset = glm::vec2(0);
		return scrollOffset;
	}

	uint32_t InputSystem::GetInputtedCharacter() const
	{
		const uint32_t character = Callbacks::characterInputted;
		Callbacks::characterInputted = 0x0;
		return character;
	}

	InputSystem& InputSystem::GetInstance()
	{
		static InputSystem instance;
		return instance;
	}
}