#include <components/drop_down.h>
#include <utilities/input_system.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	DropDown::DropDown(const Viewport& viewport, const Font* font, float fontSize) :
		m_font(font), m_fontSize(fontSize), m_optionsOffset(0.0f)
	{
		this->InitializeComponent();
		m_maxVisibleOptions = this->CalculateMaxVisibleOptions(viewport);
	}

	DropDown::~DropDown()
	{
		delete m_currentSelectedBox;
		for (auto& option : m_options)
			delete option.button;
	}

	void DropDown::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Line");
		m_triangleGeometry = *ResourceLoader::GetInstance().GetGeometry("Triangle");

		m_currentSelectedBox = new TextBox(m_font, m_fontSize, "No options available", true);
		m_currentSelectedBox->SetInputState(false); // Make the text box read-only

		m_currentSelectedBox->SetBorderColor({ 0.0f, 0.0f, 0.0f, 1.0f }, ComponentEvent::NO_EVENT);
		m_currentSelectedBox->SetBorderColor({ 0.0f, 0.0f, 0.0f, 1.0f }, ComponentEvent::HOVERED_EVENT);
		m_currentSelectedBox->SetBorderColor({ 0.0f, 0.0f, 0.0f, 1.0f }, ComponentEvent::CLICKED_EVENT);
		
		m_seperatorColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	}

	int DropDown::CalculateMaxVisibleOptions(const Viewport& viewport) const
	{
		const glm::ivec2& size = m_currentSelectedBox->GetSize();
		const float& borderThickness = m_currentSelectedBox->GetBorderThickness();
		return (int)((viewport.GetSize().y - m_currentSelectedBox->GetPosition().y - ((float)size.y / 2)) / size.y);
	}

	void DropDown::AddOption(std::string_view optionText, int valueID)
	{
		/// Precautionary checks ///
		// Make sure there isn't already an existing option with the same value ID
		for (const auto& option : m_options)
		{
			if (option.valueID == valueID)
				return;
		}

		// Make sure that the value ID given is larger than 0
		if (valueID < 0)
			return;

		/// Add the option into the drop-down ///
		// Update the drop-down hint text
		if (m_options.empty())
			m_currentSelectedBox->SetHintText("Select an option");
		
		// Setup the option object
		SelectionOption option;
		option.valueID = valueID;

		option.button = new PushButton(optionText, m_font, m_fontSize);
		option.button->SetEnabled(false);
		option.button->SetSize(m_currentSelectedBox->GetSize());

		option.button->SetClickCallback([=]() {
			this->SetCurrentSelected(option.valueID);
			m_currentSelectedBox->SetFocusState(false);
			});

		option.button->SetColor(m_currentSelectedBox->GetColor(ComponentEvent::NO_EVENT), ComponentEvent::NO_EVENT);
		option.button->SetColor(m_currentSelectedBox->GetColor(ComponentEvent::HOVERED_EVENT), ComponentEvent::HOVERED_EVENT);
		option.button->SetColor(m_currentSelectedBox->GetColor(ComponentEvent::CLICKED_EVENT), ComponentEvent::CLICKED_EVENT);
		option.button->SetBorderThickness(0);

		// Add the option object into the vector array
		m_options.emplace_back(option);
	}

	void DropDown::RemoveOption(int valueID)
	{
		for (auto it = m_options.begin(); it != m_options.end(); it++)
		{
			if (it->valueID == valueID)
			{
				m_options.erase(it);
				break;
			}
		}

		// Update the drop-down hint text
		if (m_options.empty())
			m_currentSelectedBox->SetHintText("No options available");
	}

	void DropDown::ClearSelectionList()
	{
		m_currentSelectedBox->SetHintText("No options available");
		m_currentSelectedBox->SetFocusState(false);
		m_currentSelectedValueID = -1;
		m_options.clear();
	}

	void DropDown::SetCurrentSelected(int valueID)
	{
		if (valueID < 0) // If valueID is less than 0 then set no option as current selected
		{
			m_currentSelectedBox->SetInputText(std::string());
			m_currentSelectedValueID = -1;
		}
		else
		{
			for (const auto& option : m_options)
			{
				if (option.valueID == valueID)
				{
					m_currentSelectedBox->SetInputText(option.button->GetText());
					m_currentSelectedValueID = valueID;
					break;
				}
			}
		}
	}

	void DropDown::SetPosition(glm::ivec2 pos) { m_currentSelectedBox->SetPosition(pos); }

	void DropDown::SetSize(glm::ivec2 size)
	{
		m_currentSelectedBox->SetSize(size);
		for (auto& option : m_options)
			option.button->SetSize(size);
	}

	void DropDown::SetColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		m_currentSelectedBox->SetColor(color, eventEnum);
		for (auto& option : m_options)
			option.button->SetColor(color, eventEnum);
	}

	void DropDown::SetBorderColor(glm::vec4 color, ComponentEvent eventEnum) { m_currentSelectedBox->SetBorderColor(color, eventEnum); }

	void DropDown::SetBorderThickness(int thickness) { m_currentSelectedBox->SetBorderThickness(thickness); }

	void DropDown::SetSeperatorColor(glm::vec4 color) { m_seperatorColor = color; }

	void DropDown::Update(float deltaTime)
	{
		if (m_gainedFocus)
			m_currentSelectedBox->SetFocusState(true);
		else if (m_lostFocus)
			m_currentSelectedBox->SetFocusState(false);

		if (m_currentSelectedBox->HasRequestedFocus() && !InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
			m_requestedFocus = true;

		if (m_currentSelectedBox->IsFocused()) // This means the drop-down has been activated
		{
			// Update the selection options offset via the user scrolling
			const float scrollOffsetY = InputSystem::GetInstance().GetScrollOffset().y;

			if (scrollOffsetY > 0.0f)
				m_optionsOffset = std::max(m_optionsOffset - 0.075f, 0.0f);
			else if (scrollOffsetY < 0.0f)
				m_optionsOffset = std::min(m_optionsOffset + 0.075f, (float)std::max((int)m_options.size() - m_maxVisibleOptions, 0));

			// Update the selection element buttons
			const glm::ivec2& dropDownPosition = m_currentSelectedBox->GetPosition();
			for (int i = (int)m_optionsOffset; i < std::min((int)m_optionsOffset + m_maxVisibleOptions, (int)m_options.size()); i++)
			{
				PushButton* optionButton = m_options[i].button;
				optionButton->SetPosition({ dropDownPosition.x, 
					dropDownPosition.y + (m_currentSelectedBox->GetBorderThickness() / 2) + 
					((float)((i - (int)m_optionsOffset) + 1) * optionButton->GetSize().y)});

				optionButton->SetEnabled(true);
				optionButton->Update(deltaTime);
			}
		}
		else
		{
			if (m_isFocused)
				m_isFocused = false;

			for (auto& option : m_options)
				option.button->SetEnabled(false);
		}

		// Update the current selected option box
		m_currentSelectedBox->Update(deltaTime);

		this->ResetActionFocusFlags(); // Reset the gained and lost focus flags to false
	}

	void DropDown::Render(const Viewport& viewport) const
	{
		// Render the current selection button
		m_currentSelectedBox->Render(viewport);

		if (m_currentSelectedBox->IsFocused()) // This means the drop-down has been activated
		{
			for (int i = (int)m_optionsOffset; i < std::min((int)m_optionsOffset + m_maxVisibleOptions, (int)m_options.size()); i++)
			{
				/// Render the selection option buttons ///
				const PushButton* optionButton = m_options[i].button;
				optionButton->Render(viewport);

				/// Render the line seperator ///
				if (i < std::min((int)m_optionsOffset + m_maxVisibleOptions, (int)m_options.size()) - 1)
				{
					// Construct the model matrix
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(optionButton->GetPosition().x,
						optionButton->GetPosition().y + (optionButton->GetSize().y / 2), 0.0f));
					model = glm::scale(model, glm::vec3(optionButton->GetSize().x - 20.0f, 0.0f, 0.0f));

					// Bind the shader and setup the shader uniforms
					m_shaders->Bind();
					m_shaders->SetUniform("textureSampler", 0);
					m_shaders->SetUniform("useTextures", false);
					m_shaders->SetUniformGLM("model", model);
					m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
					m_shaders->SetUniformGLM("color", m_seperatorColor);

					// Render the line
					m_geometry.vao->Bind();
					glDrawArrays(GL_LINES, 0, 2);
				}
			}

			// If drop down is scrollable, render small arrow triangles to indicate so
			if (m_options.size() > m_maxVisibleOptions)
			{
				// Bind the shader and setup the shader uniforms
				m_shaders->Bind();
				m_shaders->SetUniform("textureSampler", 0);
				m_shaders->SetUniform("useTextures", false);
				m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
				m_shaders->SetUniformGLM("color", { 0.196f, 0.196f, 0.196f, 1.0f });

				const glm::ivec2& position = m_currentSelectedBox->GetPosition();
				const glm::ivec2& size = m_currentSelectedBox->GetSize();

				if ((int)m_optionsOffset > 0)
				{
					// Construct the model matrix
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(position.x + (size.x / 2) - 20, position.y + size.y, 0.0f));
					model = glm::scale(model, glm::vec3(20.0f, 15.0f, 0.0f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

					m_shaders->SetUniformGLM("model", model);

					// Render the triangle
					m_triangleGeometry.vao->Bind();
					glDrawArrays(GL_TRIANGLES, 0, 3);
				}

				if ((int)(m_optionsOffset + m_maxVisibleOptions) < (int)m_options.size())
				{
					// Construct the model matrix
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(position.x + (size.x / 2) - 20, position.y + (m_maxVisibleOptions * size.y), 0.0f));
					model = glm::scale(model, glm::vec3(20.0f, 15.0f, 0.0f));

					m_shaders->SetUniformGLM("model", model);

					// Render the triangle
					m_triangleGeometry.vao->Bind();
					glDrawArrays(GL_TRIANGLES, 0, 3);
				}
			}
		}
	}

	int DropDown::GetSelectedOption() const { return m_currentSelectedValueID; }

	const glm::ivec2& DropDown::GetPosition() const { return m_currentSelectedBox->GetPosition(); }

	const glm::ivec2& DropDown::GetSize() const { return m_currentSelectedBox->GetSize(); }

	const glm::vec4& DropDown::GetColor(ComponentEvent eventEnum) const { return m_currentSelectedBox->GetColor(eventEnum); }

	const glm::vec4& DropDown::GetBorderColor(ComponentEvent eventEnum) const { return m_currentSelectedBox->GetBorderColor(eventEnum); }
	
	const int& DropDown::GetBorderThickness() const { return m_currentSelectedBox->GetBorderThickness(); }

	const glm::vec4& DropDown::GetSeperatorColor() const { return m_seperatorColor; }
}
