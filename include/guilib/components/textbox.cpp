#include <components/textbox.h>
#include <graphics/animation.h>
#include <utilities/input_system.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	TextBox::TextBox(const Font* font, float fontSize, std::string_view hintText, bool textCentered) :
		m_inputEnabled(true), m_isInputVisible(true), m_textCentered(textCentered)
	{
		this->InitializeComponent();

		m_hintText = new Label(hintText, { 0.4f, 0.4f, 0.4f, 1.0f }, font, fontSize);
		m_inputText = new Label("", { 0.0f, 0.0f, 0.0f, 1.0f }, font, fontSize);

		m_size.x = std::max(250, m_hintText->GetSize().x + 100);
		m_size.y = std::max(50, m_hintText->GetSize().y + 50);
	}

	TextBox::~TextBox()
	{
		delete m_hintText;
		delete m_inputText;
	}

	void TextBox::SetInputState(bool enabled) { m_inputEnabled = enabled; }

	void TextBox::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Square");

		m_position = m_size = { 0, 0 };

		m_currentColor = m_baseColor = { 0.6f, 0.6, 0.6f, 1.0f };
		m_hoverColor = { 0.8f, 0.8f, 0.8f, 1.0f };
		m_clickedColor = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_currentHintTextColor = m_baseHintTextColor = m_hoverHintTextColor = { 0.4f, 0.4f, 0.4f, 1.0f };
		m_currentInputTextColor = m_baseInputTextColor = m_hoverInputTextColor = m_clickedInputTextColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_currentBorderColor = m_baseBorderColor = m_hoverBorderColor = m_clickedBorderColor = { 0.2f, 0.2f, 0.2f, 1.0f };
		m_borderThickness = 4;
	}

	void TextBox::SetInputVisibility(bool visible) { m_isInputVisible = visible; }

	void TextBox::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void TextBox::SetSize(glm::ivec2 size) { m_size = size; }

	void TextBox::SetHintText(std::string_view text) { m_hintText->SetText(text); }

	void TextBox::SetInputText(std::string_view text) 
	{ 
		if (m_isInputVisible)
			m_inputText->SetText(text);
		else
		{
			m_obscuredInputText = text;
			m_inputText->SetText(std::string(text.size(), '#'));
		}
	}

	void TextBox::SetColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentColor = m_baseColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedColor = color;
	}

	void TextBox::SetHintTextColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentHintTextColor = m_baseHintTextColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverHintTextColor = color;
	}

	void TextBox::SetInputTextColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentInputTextColor = m_baseInputTextColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverInputTextColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedInputTextColor = color;
	}

	void TextBox::SetBorderColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentBorderColor = m_baseBorderColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverBorderColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedBorderColor = color;
	}

	void TextBox::SetBorderThickness(int thickness) { m_borderThickness = thickness; }
	
	bool TextBox::IsCursorHovering() const
	{
		const glm::vec2 cursorPosition = InputSystem::GetInstance().GetCursorPosition();

		return
			cursorPosition.x >= m_position.x - (m_size.x / 2.0f) && cursorPosition.x <= m_position.x + (m_size.x / 2.0f) &&
			cursorPosition.y >= m_position.y - (m_size.y / 2.0f) && cursorPosition.y <= m_position.y + (m_size.y / 2.0f);
	}

	void TextBox::Update(float deltaTime)
	{
		// Update the text field color and focus state
		if (this->IsCursorHovering())
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT) && !m_isFocused)
			{
				m_currentColor = m_clickedColor;
				m_currentInputTextColor = m_clickedInputTextColor;
				m_currentBorderColor = m_clickedBorderColor;

				m_requestedFocus = true;
			}
			else
			{
				if (!m_isFocused)
				{
					if (m_lostFocus)
					{
						m_currentColor = m_hoverColor;
						m_currentHintTextColor = m_hoverHintTextColor;
						m_currentInputTextColor = m_hoverInputTextColor;
						m_currentBorderColor = m_hoverBorderColor;
					}
					else
					{
						m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_baseColor, m_hoverColor, 8.0f, deltaTime);
						m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_baseBorderColor, m_hoverBorderColor, 8.0f, deltaTime);

						m_currentHintTextColor = FadeTo<glm::vec4>(m_currentHintTextColor, m_baseHintTextColor, m_hoverHintTextColor, 8.0f, 
							deltaTime);

						m_currentInputTextColor = FadeTo<glm::vec4>(m_currentInputTextColor, m_baseInputTextColor, m_hoverInputTextColor, 8.0f, 
							deltaTime);
					}
				}
			}
		}
		else
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
				m_isFocused = false;

			if (!m_isFocused)
			{
				m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_hoverColor, m_baseColor, 8.0f, deltaTime);
				m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_hoverBorderColor, m_baseBorderColor, 8.0f, deltaTime);
				m_currentHintTextColor = FadeTo<glm::vec4>(m_currentHintTextColor, m_hoverHintTextColor, m_baseHintTextColor, 8.0f, deltaTime);
				m_currentInputTextColor = FadeTo<glm::vec4>(m_currentInputTextColor, m_hoverInputTextColor, m_baseInputTextColor, 8.0f, 
					deltaTime);
			}
		}

		// Check if user entered any text (if focused)
		if (m_isFocused && m_inputEnabled)
		{
			const char inputtedChar = (char)GUILib::InputSystem::GetInstance().GetInputtedCharacter();
			std::string currentInputText = m_isInputVisible ? m_inputText->GetText() : m_obscuredInputText;

			if (inputtedChar > 0 && !m_gainedFocus)
				currentInputText += inputtedChar;
			else if (!currentInputText.empty() && InputSystem::GetInstance().WasKeyPressed(KeyCode::KEY_BACKSPACE) && 
				m_backspaceTimer.GetElapsedTime() >= 0.2f)
			{
				currentInputText.pop_back();
				m_backspaceTimer.Reset();
			}

			if (m_isInputVisible)
				m_inputText->SetText(currentInputText);
			else
			{
				m_obscuredInputText = currentInputText;
				m_inputText->SetText(std::string(m_obscuredInputText.size(), '#'));
			}
		}

		// Update the positions of the text in the field
		const glm::ivec2& inputTextSize = m_inputText->GetSize();
		const glm::ivec2& hintTextSize = m_hintText->GetSize();

		if (!m_textCentered)
		{
			m_inputText->SetPosition({ m_position.x - (m_size.x / 2) + 15, m_position.y + (inputTextSize.y / 2) });
			m_hintText->SetPosition({ m_position.x - (m_size.x / 2) + 15, m_position.y + (hintTextSize.y / 2) });
		}
		else
		{
			m_inputText->SetPosition({ m_position.x - (inputTextSize.x / 2), m_position.y + (inputTextSize.y / 2) });
			m_hintText->SetPosition({ m_position.x - (hintTextSize.x / 2), m_position.y + (hintTextSize.y / 2) });
		}

		if (!m_inputText->GetText().empty())
		{
			m_inputText->SetTextColor(m_currentInputTextColor);
			m_inputText->Update(deltaTime);
		}
		else if (!m_isFocused)
		{
			m_hintText->SetTextColor(m_currentHintTextColor);
			m_hintText->Update(deltaTime);
		}

		this->ResetActionFocusFlags(); // Reset the gained and lost focus flags to false
	}

	void TextBox::Render(const Viewport& viewport) const
	{
		/// Render the border first ///
		// Construct the model matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_size + m_borderThickness, 0.0f });

		// Bind the shader and setup the shader uniforms
		m_shaders->Bind();
		m_shaders->SetUniform("textureSampler", 0);
		m_shaders->SetUniform("useTextures", false);
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
		m_shaders->SetUniformGLM("color", m_currentBorderColor);

		// Render the border
		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/// Render the text field ///
		// Construct the model matrix
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_size, 0.0f });

		// Setup the shader uniforms
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("color", m_currentColor);

		// Render the text field
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/// Render the text in the field ///
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);

		if (!m_inputText->GetText().empty())
			m_inputText->Render(viewport);
		else if (!m_isFocused)
			m_hintText->Render(viewport);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
	}

	const glm::ivec2& TextBox::GetPosition() const { return m_position; }
	
	const glm::ivec2& TextBox::GetSize() const { return m_size; }

	const std::string& TextBox::GetHintText() const { return m_hintText->GetText(); }

	const std::string& TextBox::GetInputText() const { return m_isInputVisible ? m_inputText->GetText() : m_obscuredInputText; }

	const glm::vec4& TextBox::GetColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedColor;
		}

		return m_baseColor;
	}

	const glm::vec4& TextBox::GetHintTextColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseHintTextColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverHintTextColor;
		}

		return m_baseHintTextColor;
	}

	const glm::vec4& TextBox::GetInputTextColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseInputTextColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverInputTextColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedInputTextColor;
		}

		return m_baseInputTextColor;
	}

	const glm::vec4& TextBox::GetBorderColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseBorderColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverBorderColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedBorderColor;
		}

		return m_baseBorderColor;
	}
	
	const int& TextBox::GetBorderThickness() const { return m_borderThickness; }
}