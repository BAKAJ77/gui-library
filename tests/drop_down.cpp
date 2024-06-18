#include <guilib/guilib.h>
#include <guilib/components/drop_down.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Dropdown Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font from file
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const GUILib::Font* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		// Setup user interface
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		frame->SetBackgroundColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		GUILib::DropDown* dropDown = new GUILib::DropDown(frame->GetViewport(), font, 24);
		dropDown->SetPosition({ 300, 200 });
		dropDown->SetSize({ 300, 40 });

		dropDown->AddOption("Option 1", 0);
		dropDown->AddOption("Option 2", 1);
		dropDown->AddOption("Option 3", 2);
		dropDown->AddOption("Option 4", 3);
		dropDown->AddOption("Option 5", 4);
		dropDown->AddOption("Option 6", 5);
		dropDown->AddOption("Option 7", 6);
		dropDown->AddOption("Option 8", 7);
		dropDown->AddOption("Option 9", 8);
		dropDown->AddOption("Option 10", 9);

		frame->AddComponent("Dropdown", dropDown);

		while (!glfwWindowShouldClose(window))
		{
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