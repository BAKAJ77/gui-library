#include <guilib/guilib.h>
#include <guilib/components/textbox.h>
#include <guilib/components/push_button.h>
#include <guilib/components/radio_group.h>
#include <guilib/components/drop_down.h>

#include <assets_path.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace GUILib;

const Font* arial = nullptr;
InterfaceFrame* mainMenuPage = nullptr, *signupPage = nullptr, *loginPage = nullptr;

std::string username, name, gender;

static void DefineButtonStyle(Button* button)
{
	button->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f }, ComponentEvent::NO_EVENT);
	button->SetColor({ 0.3f, 0.3f, 0.3f, 1.0f }, ComponentEvent::HOVERED_EVENT);
	button->SetColor({ 0.4f, 0.4f, 0.4f, 1.0f }, ComponentEvent::CLICKED_EVENT);

	button->SetBorderThickness(0);
}

static void SetupMainMenuComponents()
{
	// Setup the label
	Label* label = new Label("No account is logged in at the moment.", glm::vec4(1.0f), arial, 26);
	Label* dropDownLabel = new Label("Choose the account information to display:", glm::vec4(1.0f), arial, 24);
	Label* accountInfoText = new Label("", glm::vec4(1.0f), arial, 20);
	label->SetPosition({ 250 - label->GetSize().x / 2, 120 });
	dropDownLabel->SetPosition({ 250 - dropDownLabel->GetSize().x / 2, 200 });
	accountInfoText->SetPosition({ 250 - accountInfoText->GetSize().x / 2, 280 });

	dropDownLabel->SetEnabled(false);
	accountInfoText->SetEnabled(false);

	// Setup the drop-down
	DropDown* accountInfoDropDown = new DropDown(mainMenuPage->GetViewport(), arial, 20);
	accountInfoDropDown->AddOption("Username", 0);
	accountInfoDropDown->AddOption("Full Name", 1);
	accountInfoDropDown->AddOption("Gender", 2);

	accountInfoDropDown->SetPosition({ 250, 240 });
	accountInfoDropDown->SetSize({ 200, 40 });
	accountInfoDropDown->SetEnabled(false);

	// Setup the login and signup buttons
	PushButton* loginBtn = new PushButton("Log In", arial, 40);
	loginBtn->SetSize({ 200, 70 });
	loginBtn->SetPosition({ 384, 445 });
	loginBtn->SetClickCallback([=]() { mainMenuPage->SetEnabled(false); loginPage->SetEnabled(true); });

	DefineButtonStyle(loginBtn);

	PushButton* signupBtn = new PushButton("Sign Up", arial, 40);
	signupBtn->SetSize({ 200, 70 });
	signupBtn->SetPosition({ 116, 445 });
	signupBtn->SetClickCallback([=]() { mainMenuPage->SetEnabled(false); signupPage->SetEnabled(true); });
	
	DefineButtonStyle(signupBtn);

	mainMenuPage->AddComponent("Label", label);
	mainMenuPage->AddComponent("DropDownLabel", dropDownLabel);
	mainMenuPage->AddComponent("AccountInfoLabel", accountInfoText);
	mainMenuPage->AddComponent("DropDown", accountInfoDropDown);
	mainMenuPage->AddComponent("Login", loginBtn);
	mainMenuPage->AddComponent("Signup", signupBtn);
}

static void SetupSignupPageComponents()
{
	// Setup the labels
	Label* fnLabel = new Label("First Name: ", glm::vec4(1.0f), arial, 20);
	fnLabel->SetPosition({ 20, 60 });

	Label* lnLabel = new Label("Last Name: ", glm::vec4(1.0f), arial, 20);
	lnLabel->SetPosition({ 20, 120 });

	Label* usrnmLabel = new Label("Username: ", glm::vec4(1.0f), arial, 20);
	usrnmLabel->SetPosition({ 20, 180 });

	Label* passwrdLabel = new Label("Password: ", glm::vec4(1.0f), arial, 20);
	passwrdLabel->SetPosition({ 20, 240 });

	Label* genderSelectLabel = new Label("Select a gender below", glm::vec4(1.0f), arial, 20);
	genderSelectLabel->SetPosition({ 20, 300 });

	Label* formErrorLabel = new Label("Make sure you've filled all the data required", { 1.0f, 0.0f, 0.0f, 1.0f }, arial, 20);
	formErrorLabel->SetPosition({ 250 - (formErrorLabel->GetSize().x / 2), 400});
	formErrorLabel->SetEnabled(false);

	signupPage->AddComponent("FirstNameLabel", fnLabel);
	signupPage->AddComponent("LastNameLabel", lnLabel);
	signupPage->AddComponent("UsernameLabel", usrnmLabel);
	signupPage->AddComponent("PasswordLabel", passwrdLabel);
	signupPage->AddComponent("GenderSelectLabel", genderSelectLabel);
	signupPage->AddComponent("FormErrorLabel", formErrorLabel);

	// Setup the textboxes
	TextBox* fnTextbox = new TextBox(arial, 20, "Enter your first name here");
	fnTextbox->SetSize({ 300, 40 });
	fnTextbox->SetPosition({ 300, fnLabel->GetPosition().y - (fnLabel->GetSize().y / 2) });

	fnTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	TextBox* lnTextbox = new TextBox(arial, 20, "Enter your last name here");
	lnTextbox->SetSize({ 300, 40 });
	lnTextbox->SetPosition({ 300, lnLabel->GetPosition().y - (lnLabel->GetSize().y / 2) });

	lnTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	TextBox* usrnmTextbox = new TextBox(arial, 20, "Enter a username here");
	usrnmTextbox->SetSize({ 300, 40 });
	usrnmTextbox->SetPosition({ 300, usrnmLabel->GetPosition().y - (usrnmLabel->GetSize().y / 2) });

	usrnmTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	TextBox* passwrdTextbox = new TextBox(arial, 20, "Enter a password here");
	passwrdTextbox->SetSize({ 300, 40 });
	passwrdTextbox->SetPosition({ 300, passwrdLabel->GetPosition().y - (passwrdLabel->GetSize().y / 2) });
	passwrdTextbox->SetInputVisibility(false);

	passwrdTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	signupPage->AddComponent("FirstNameTextbox", fnTextbox);
	signupPage->AddComponent("LastNameTextbox", lnTextbox);
	signupPage->AddComponent("UsernameTextbox", usrnmTextbox);
	signupPage->AddComponent("PasswordTextbox", passwrdTextbox);

	// Setup the radio button group
	RadioGroup* genderOptions = new RadioGroup();
	genderOptions->SetPosition({ 20, genderSelectLabel->GetPosition().y + 40 });

	genderOptions->AddOption({ new RadioButton(), new Label("Male", glm::vec4(1.0f), arial, 17), 0 });
	genderOptions->AddOption({ new RadioButton(), new Label("Female", glm::vec4(1.0f), arial, 17), 1 });
	genderOptions->AddOption({ new RadioButton(), new Label("Other", glm::vec4(1.0f), arial, 17), 2 });

	signupPage->AddComponent("GenderOptions", genderOptions);

	// Setup the back button
	PushButton* backBtn = new PushButton("Back", arial, 30);
	backBtn->SetSize({ 200, 50 });
	backBtn->SetPosition({ 120, 455 });
	backBtn->SetClickCallback([=]() {
		fnTextbox->SetInputText(std::string());
		lnTextbox->SetInputText(std::string());
		usrnmTextbox->SetInputText(std::string());
		passwrdTextbox->SetInputText(std::string());
		genderOptions->SetSelectedOption(-1);
		formErrorLabel->SetEnabled(false);

		signupPage->SetEnabled(false);
		mainMenuPage->SetEnabled(true);
		});

	// Setup the confirm signup button
	PushButton* confirmSignupBtn = new PushButton("Sign Up", arial, 30);
	confirmSignupBtn->SetSize({ 200, 50 });
	confirmSignupBtn->SetPosition({ 380, 455 });
	confirmSignupBtn->SetClickCallback([=]() {
		if (!fnTextbox->GetInputText().empty() && !lnTextbox->GetInputText().empty() && !usrnmTextbox->GetInputText().empty() &&
			!passwrdTextbox->GetInputText().empty() && genderOptions->GetSelectedOption() >= 0)
		{
			std::ofstream file("account_data.txt");
			file << usrnmTextbox->GetInputText() << "," << passwrdTextbox->GetInputText() << "," << fnTextbox->GetInputText() << "," <<
				lnTextbox->GetInputText() << "," << genderOptions->GetSelectedOption() << "\n";

			fnTextbox->SetInputText(std::string());
			lnTextbox->SetInputText(std::string());
			usrnmTextbox->SetInputText(std::string());
			passwrdTextbox->SetInputText(std::string());
			genderOptions->SetSelectedOption(-1);
			
			signupPage->SetEnabled(false);
			mainMenuPage->SetEnabled(true);
		}
		else
			formErrorLabel->SetEnabled(true);
		});

	signupPage->AddComponent("Back", backBtn);
	signupPage->AddComponent("Signup", confirmSignupBtn);
}

static void SetupLoginPageComponents()
{
	// Setup the labels
	Label* usrnmLabel = new Label("Username: ", glm::vec4(1.0f), arial, 20);
	usrnmLabel->SetPosition({ 20, 60 });

	Label* passwrdLabel = new Label("Password: ", glm::vec4(1.0f), arial, 20);
	passwrdLabel->SetPosition({ 20, 120 });

	Label* formErrorLabel = new Label("Make sure you've filled all the data required", { 1.0f, 0.0f, 0.0f, 1.0f }, arial, 20);
	formErrorLabel->SetPosition({ 250 - (formErrorLabel->GetSize().x / 2), 400 });
	formErrorLabel->SetEnabled(false);

	Label* formErrorLabel2 = new Label("Invalid username or password", { 1.0f, 0.0f, 0.0f, 1.0f }, arial, 20);
	formErrorLabel2->SetPosition({ 250 - (formErrorLabel2->GetSize().x / 2), 400 });
	formErrorLabel2->SetEnabled(false);

	loginPage->AddComponent("UsernameLabel", usrnmLabel);
	loginPage->AddComponent("PasswordLabel", passwrdLabel);
	loginPage->AddComponent("DataRequiredLabel", formErrorLabel);
	loginPage->AddComponent("InvalidData", formErrorLabel2);

	// Setup the textboxes
	TextBox* usrnmTextbox = new TextBox(arial, 20, "Enter a username here");
	usrnmTextbox->SetSize({ 300, 40 });
	usrnmTextbox->SetPosition({ 300, usrnmLabel->GetPosition().y - (usrnmLabel->GetSize().y / 2) });

	usrnmTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	TextBox* passwrdTextbox = new TextBox(arial, 20, "Enter a password here");
	passwrdTextbox->SetSize({ 300, 40 });
	passwrdTextbox->SetPosition({ 300, passwrdLabel->GetPosition().y - (passwrdLabel->GetSize().y / 2) });
	passwrdTextbox->SetInputVisibility(false);

	passwrdTextbox->SetBorderColor({ 0.5f, 0.5f, 0.5f, 1.0f },
		ComponentEvent::NO_EVENT | ComponentEvent::HOVERED_EVENT | ComponentEvent::CLICKED_EVENT);

	loginPage->AddComponent("UsernameTextbox", usrnmTextbox);
	loginPage->AddComponent("PasswordTextbox", passwrdTextbox);

	// Setup the back button
	PushButton* backBtn = new PushButton("Back", arial, 30);
	backBtn->SetSize({ 200, 50 });
	backBtn->SetPosition({ 120, 455 });
	backBtn->SetClickCallback([=]() {
		usrnmTextbox->SetInputText(std::string());
		passwrdTextbox->SetInputText(std::string());
		formErrorLabel->SetEnabled(false);
		formErrorLabel2->SetEnabled(false);

		loginPage->SetEnabled(false);
		mainMenuPage->SetEnabled(true);
		});

	// Setup the login button
	PushButton* confirmLoginBtn = new PushButton("Log In", arial, 30);
	confirmLoginBtn->SetSize({ 200, 50 });
	confirmLoginBtn->SetPosition({ 380, 455 });
	confirmLoginBtn->SetClickCallback([=]() {
		if (!usrnmTextbox->GetInputText().empty() && !passwrdTextbox->GetInputText().empty())
		{
			formErrorLabel->SetEnabled(false);

			std::vector<std::string> accounts, tokens;

			// Read accounts file
			std::ifstream file("account_data.txt");
			std::string readLine;
			while (std::getline(file, readLine))
				accounts.emplace_back(readLine);

			// Loop through each account
			bool accountFound = false;
			for (const auto& account : accounts)
			{
				// Tokenize account data string
				std::string token;
				std::stringstream ss;
				ss << account;
				
				while (std::getline(ss, token, ','))
					tokens.emplace_back(token);

				if (usrnmTextbox->GetInputText() == tokens[0] && passwrdTextbox->GetInputText() == tokens[1])
				{
					accountFound = true;
					break;
				}
			}

			if (accountFound)
			{
				formErrorLabel2->SetEnabled(false);

				username = tokens[0];
				name = tokens[2] + " " + tokens[3];

				if (tokens[4] == "0")
					gender = "Male";
				else if (tokens[4] == "1")
					gender = "Female";
				else
					gender = "Other";

				usrnmTextbox->SetInputText(std::string());
				passwrdTextbox->SetInputText(std::string());

				loginPage->SetEnabled(false);
				mainMenuPage->SetEnabled(true);
			}
			else
				formErrorLabel2->SetEnabled(true);

			passwrdTextbox->SetInputText(std::string());
		}
		else
		{
			formErrorLabel->SetEnabled(true);
			formErrorLabel2->SetEnabled(false);
		}
		});

	loginPage->AddComponent("Back", backBtn);
	loginPage->AddComponent("Login", confirmLoginBtn);
}

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
		glfwWindowHint(GLFW_SAMPLES, 4);

		GLFWwindow* window = glfwCreateWindow(500, 500, "Login Form App", nullptr, nullptr);
		if (!window)
			throw std::exception("Failed to create GLFW window");

		glfwMakeContextCurrent(window);
		GUILib::InitLibraryGLFWImpl(window, (GLADloadproc)glfwGetProcAddress);

		// Load the arial font from file
		ResourceLoader::GetInstance().LoadFontFromFile("Arial", LIB_EXAMPLES_ASSETS_PATH + std::string("arial.ttf"));
		arial = ResourceLoader::GetInstance().GetFont("Arial");
		
		// Setup user interface
		mainMenuPage = new GUILib::InterfaceFrame(Viewport({ 0, 0 }, { 500, 500 }));
		mainMenuPage->SetBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		signupPage = new GUILib::InterfaceFrame(Viewport({ 0, 0 }, { 500, 500 }));
		signupPage->SetBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		signupPage->SetEnabled(false);

		loginPage = new GUILib::InterfaceFrame(Viewport({ 0, 0 }, { 500, 500 }));
		loginPage->SetBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		loginPage->SetEnabled(false);

		SetupMainMenuComponents();
		SetupSignupPageComponents();
		SetupLoginPageComponents();

		while (!glfwWindowShouldClose(window))
		{
			if (!username.empty() && !name.empty() && !gender.empty())
			{
				Label* text = (Label*)mainMenuPage->GetComponent("Label");
				Label* dropDownLabel = (Label*)mainMenuPage->GetComponent("DropDownLabel");
				Label* accountInfoText = (Label*)mainMenuPage->GetComponent("AccountInfoLabel");
				DropDown* accountInfoDropDown = (DropDown*)mainMenuPage->GetComponent("DropDown");

				dropDownLabel->SetEnabled(true);
				accountInfoDropDown->SetEnabled(true);

				text->SetText("You are logged in!");
				text->SetPosition({ 250 - text->GetSize().x / 2, 120 });

				switch (accountInfoDropDown->GetSelectedOption())
				{
				case 0:
					accountInfoText->SetText("Username: " + username);
					break;
				case 1:
					accountInfoText->SetText("Full Name: " + name);
					break;
				case 2:
					accountInfoText->SetText("Gender: " + gender);
					break;
				}

				accountInfoText->SetPosition({ 250 - accountInfoText->GetSize().x / 2, 300 });

				if (accountInfoDropDown->GetSelectedOption() >= 0)
					accountInfoText->SetEnabled(true);
			}

			// Do GUI stuff here
			mainMenuPage->Update();
			mainMenuPage->Render();

			signupPage->Update();
			signupPage->Render();

			loginPage->Update();
			loginPage->Render();

			// Poll for events and swap render buffers
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		delete mainMenuPage;
		delete signupPage;

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