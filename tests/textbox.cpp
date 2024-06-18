#include <guilib/guilib.h>
#include <guilib/components/textbox.h>
#include <guilib/utilities/input_system.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Textbox Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font from file
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const GUILib::Font* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		// Setup user interface
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		frame->SetBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		GUILib::TextBox* fnameTextField = new GUILib::TextBox(font, 24, "Enter your first name here");
		GUILib::TextBox* lnameTextField = new GUILib::TextBox(font, 24, "Enter your last name here");
		GUILib::Label* instructionText = new GUILib::Label("Press Enter to submit!", { 0.0f, 1.0f, 0.0f, 1.0f }, font, 24);
		GUILib::Label* text = new GUILib::Label("", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 24);

		fnameTextField->SetPosition({ 300, 250 });
		lnameTextField->SetPosition({ 300, 350 });
		instructionText->SetPosition({ 300 - (instructionText->GetSize().x / 2), 500 });
		text->SetEnabled(false);
		
		frame->AddComponent("FirstNameTextField", fnameTextField);
		frame->AddComponent("LastNameTextField", lnameTextField);
		frame->AddComponent("InstructionTextLabel", instructionText);
		frame->AddComponent("TextLabel", text);

		while (!glfwWindowShouldClose(window))
		{
			if (GUILib::InputSystem::GetInstance().WasKeyPressed(GUILib::KeyCode::KEY_ENTER) && !fnameTextField->GetInputText().empty() && 
				!lnameTextField->GetInputText().empty())
			{
				text->SetEnabled(true);
				text->SetText("Your name is: " + fnameTextField->GetInputText() + " " + lnameTextField->GetInputText());
				text->SetPosition({ 300 - (text->GetSize().x / 2), 450 });
			}

			// Do GUI stuff here
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