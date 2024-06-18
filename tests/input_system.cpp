#include <guilib/components/label.h>
#include <guilib/utilities/input_system.h>
#include <guilib/guilib.h>
#include <assets_path.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char** argv)
{
	try
	{
		// Initialize GLFW library
		if (!glfwInit())
			throw std::exception("Failed to initialize GLFW");

		// Setup window hints and create GLFW window
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

		GLFWwindow* window = glfwCreateWindow(600, 600, "Input System Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load arial font
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const GUILib::Font* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		// Setup user interface
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		GUILib::Label* cursorPosLabel = new GUILib::Label("", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 25);
		GUILib::Label* scrollOffsetLabel = new GUILib::Label("", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 25);
		GUILib::Label* enteredCharsLabel = new GUILib::Label("Entered Characters: ", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 25);
		GUILib::Label* quitInstructionLabel = new GUILib::Label("Press Enter or click LMB to quit!", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 25);
		
		quitInstructionLabel->SetPosition({ 300 - (quitInstructionLabel->GetSize().x / 2), 525 });

		frame->AddComponent("CursorPosition", cursorPosLabel);
		frame->AddComponent("ScrollOffset", scrollOffsetLabel);
		frame->AddComponent("EnteredCharacters", enteredCharsLabel);
		frame->AddComponent("QuitInstruction", quitInstructionLabel);

		glm::vec2 scrollOffsetTotal = { 0, 0 };
		while (!glfwWindowShouldClose(window))
		{
			if (GUILib::InputSystem::GetInstance().WasKeyPressed(GUILib::KeyCode::KEY_ENTER) ||
				GUILib::InputSystem::GetInstance().WasMouseButtonPressed(GUILib::MouseButtonCode::MOUSE_BUTTON_LEFT))
				break;

			// Do GUI stuff here
			scrollOffsetTotal += GUILib::InputSystem::GetInstance().GetScrollOffset();
			const glm::vec2 cursorPosition = GUILib::InputSystem::GetInstance().GetCursorPosition(&frame->GetViewport());
			const char inputtedChar = (char)GUILib::InputSystem::GetInstance().GetInputtedCharacter();

			cursorPosLabel->SetText("Current Cursor Position: { " + std::to_string((int)cursorPosition.x) + ", " + 
				std::to_string((int)cursorPosition.y) + " }");

			scrollOffsetLabel->SetText("Scroll Offset Total: { " + std::to_string(scrollOffsetTotal.x) + ", " + 
				std::to_string(scrollOffsetTotal.y) + " }");

			if (inputtedChar > 0)
				enteredCharsLabel->SetText(enteredCharsLabel->GetText() + inputtedChar);

			cursorPosLabel->SetPosition({ 300 - (cursorPosLabel->GetSize().x / 2), 75 });
			scrollOffsetLabel->SetPosition({ 300 - (scrollOffsetLabel->GetSize().x / 2), 150 });
			enteredCharsLabel->SetPosition({ 300 - (enteredCharsLabel->GetSize().x / 2), 225 });

			frame->Update();
			frame->Render();

			// Poll for events and swap render buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		delete frame;
		GUILib::FreeLibrary();

		// Cleanup application
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}

	return EXIT_SUCCESS;
}