#include <guilib/guilib.h>
#include <guilib/components/label.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Label Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font from file
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const GUILib::Font* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		// Setup user interface consisting of 3 labels
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		GUILib::Label* label = new GUILib::Label("Hello World", { 1.0f, 0.0f, 0.0f, 1.0f }, font, 64);
		GUILib::Label* label2 = new GUILib::Label("Another string of text?", { 0.0f, 1.0f, 0.0f, 1.0f }, font, 48);
		GUILib::Label* label3 = new GUILib::Label("Why not?", { 1.0f, 0.0f, 1.0f, 1.0f }, font, 32);

		label->SetPosition({0, label->GetSize().y});
		label2->SetPosition({ 300 - (label2->GetSize().x / 2), 300 + (label2->GetSize().y / 2) });
		label3->SetPosition({600 - label3->GetSize().x, 595});

		frame->AddComponent("Label1", label);
		frame->AddComponent("Label2", label2);
		frame->AddComponent("Label3", label3);

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