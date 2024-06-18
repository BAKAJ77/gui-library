#include <guilib/guilib.h>
#include <guilib/components/image.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Image Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the test textures from file
		GUILib::ResourceLoader::GetInstance().LoadTextureFromFile("Test-Image1", LIB_TEST_ASSETS_PATH + std::string("image_test.png"), false);
		GUILib::ResourceLoader::GetInstance().LoadTextureFromFile("Test-Image2", LIB_TEST_ASSETS_PATH + std::string("image_test2.png"), false);

		// Setup user interface consisting of 2 image components
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		GUILib::Image* imageComponent = new GUILib::Image(GUILib::ResourceLoader::GetInstance().GetTexture("Test-Image1"));
		imageComponent->SetPosition({ 200, 200 });
		imageComponent->SetSize({ 150, 150 });

		GUILib::Image* imageComponent2 = new GUILib::Image(GUILib::ResourceLoader::GetInstance().GetTexture("Test-Image2"));
		imageComponent2->SetPosition({ 400, 300 });
		imageComponent2->SetSize({ 125, 125 });

		frame->AddComponent("Test-Image", imageComponent);
		frame->AddComponent("Test-Image2", imageComponent2);

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