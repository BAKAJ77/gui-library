#include <guilib/guilib.h>
#include <guilib/components/icon_button.h>
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

		GLFWwindow* window = glfwCreateWindow(600, 600, "Icon Button Test", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font and icon textures
		GUILib::ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_TEST_ASSETS_PATH + std::string("arial.ttf"));
		const auto* font = GUILib::ResourceLoader::GetInstance().GetFont("Arial");

		const auto* wifiIconTexture = GUILib::ResourceLoader::GetInstance().LoadTextureFromFile(
			LIB_TEST_ASSETS_PATH + std::string("wifi_icon.png"), false);
		const auto* homeIconTexture = GUILib::ResourceLoader::GetInstance().LoadTextureFromFile(
			LIB_TEST_ASSETS_PATH + std::string("home_icon.png"), false);
		const auto* refreshIconTexture = GUILib::ResourceLoader::GetInstance().LoadTextureFromFile
		(LIB_TEST_ASSETS_PATH + std::string("refresh_icon.png"), false);

		// Setup user interface
		GUILib::InterfaceFrame* frame = new GUILib::InterfaceFrame();
		frame->SetBackgroundColor({ 0.05f, 0.05f, 0.05f, 1.0f });

		GUILib::IconButton* wifiIcon = new GUILib::IconButton(wifiIconTexture);
		GUILib::IconButton* homeIcon = new GUILib::IconButton(homeIconTexture);
		GUILib::IconButton* refreshIcon = new GUILib::IconButton(refreshIconTexture);

		GUILib::Label* wifiLabel = new GUILib::Label("This is a wifi icon button.", { 0.3f, 0.3f, 0.3f, 1.0f }, font, 32);
		GUILib::Label* homeLabel = new GUILib::Label("This is a home icon button.", { 0.3f, 0.3f, 0.3f, 1.0f }, font, 32);
		GUILib::Label* refreshLabel = new GUILib::Label("This is a refresh icon button.", { 0.3f, 0.3f, 0.3f, 1.0f }, font, 32);

		wifiLabel->SetPosition({ 160, 110 });
		homeLabel->SetPosition({ 160, 310 });
		refreshLabel->SetPosition({ 160, 510 });

		wifiLabel->SetEnabled(false);
		homeLabel->SetEnabled(false);
		refreshLabel->SetEnabled(false);

		wifiIcon->SetPosition({ 100, 100 });
		homeIcon->SetPosition({ 100, 300 });
		refreshIcon->SetPosition({ 100, 500 });

		wifiIcon->SetClickCallback([&]() { wifiLabel->SetEnabled(!wifiLabel->IsEnabled()); });
		homeIcon->SetClickCallback([&]() { homeLabel->SetEnabled(!homeLabel->IsEnabled()); });
		refreshIcon->SetClickCallback([&]() { refreshLabel->SetEnabled(!refreshLabel->IsEnabled()); });

		frame->AddComponent("WifiIcon", wifiIcon);
		frame->AddComponent("HomeIcon", homeIcon);
		frame->AddComponent("RefreshIcon", refreshIcon);

		frame->AddComponent("WifiLabel", wifiLabel);
		frame->AddComponent("HomeLabel", homeLabel);
		frame->AddComponent("RefreshLabel", refreshLabel);

		while (!glfwWindowShouldClose(window))
		{
			// Do GUI stuff here
			frame->Update();
			frame->Render();

			// Poll for events and swap render buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		delete wifiIconTexture;
		delete homeIconTexture;
		delete refreshIconTexture;
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