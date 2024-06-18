#include <guilib/guilib.h>
#include <guilib/components/push_button.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Button Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font from file
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const GUILib::Font* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		// Setup user interface
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		
		GUILib::Button* button = new GUILib::PushButton("Click Me!", font, 48);
		GUILib::Label* counterLabel = new GUILib::Label("", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 25);
		button->SetPosition({ 300, 300 });
		
		int buttonClickedCounter = 0;
		button->SetClickCallback([&]() { buttonClickedCounter++; });
		button->SetBorderColor(glm::vec4(1.0f), GUILib::ComponentEvent::NO_EVENT);
		button->SetBorderColor(glm::vec4(1.0f), GUILib::ComponentEvent::HOVERED_EVENT);
		button->SetBorderColor(glm::vec4(1.0f), GUILib::ComponentEvent::CLICKED_EVENT);

		frame->AddComponent("Button1", button);
		frame->AddComponent("CounterLabel", counterLabel);

		while (!glfwWindowShouldClose(window))
		{
			counterLabel->SetText("You have clicked me " + std::to_string(buttonClickedCounter) + " times!");
			counterLabel->SetPosition({ 300 - (counterLabel->GetSize().x / 2), 500 });

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