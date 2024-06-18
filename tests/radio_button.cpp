#include <guilib/guilib.h>
#include <guilib/components/radio_group.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Radio Buttons Test", nullptr, nullptr);
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
		
		GUILib::RadioGroup* rg = new GUILib::RadioGroup(30);
		GUILib::Label* label = new GUILib::Label(std::string(), { 1.0f, 0.0f, 1.0f, 1.0f }, font, 32);

		rg->AddOption({ new GUILib::RadioButton(), new GUILib::Label("Option 1", glm::vec4(1.0f), font, 17), 1 });
		rg->AddOption({ new GUILib::RadioButton(), new GUILib::Label("Option 2", glm::vec4(1.0f), font, 17), 2 });
		rg->AddOption({ new GUILib::RadioButton(), new GUILib::Label("Option 3", glm::vec4(1.0f), font, 17), 3 });
		rg->SetPosition({ 125, 200 });
		
		frame->AddComponent("RadioGroup", rg);
		frame->AddComponent("Label", label);

		while (!glfwWindowShouldClose(window))
		{
			if (rg->GetSelectedOption() < 0)
				label->SetText("You have selected no option yet...");
			else
				label->SetText("You have selected option " + std::to_string(rg->GetSelectedOption()) + "!");

			label->SetPosition({ 300 - (label->GetSize().x / 2), 400 });

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