#include <components/push_button.h>
#include <utilities/input_system.h>
#include <graphics/animation.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	PushButton::PushButton(std::string_view text, const Font* font, float fontSize)
	{
		this->InitializeComponent(); 
		
		m_text = new Label(text, glm::vec4(1.0f), font, fontSize);
		const glm::ivec2& textSize = m_text->GetSize();

		m_size = textSize + 50;
		m_text->SetPosition({ m_position.x + ((m_size.x / 2) - (textSize.x / 2)), m_position.y + (m_size.y / 2) + (textSize.y / 2) });
	}

	PushButton::~PushButton() { delete m_text; }

	void PushButton::InitializeComponent()
	{
		m_text = nullptr;
		
		m_currentColor = m_baseColor = { 0.011f, 0.419f, 0.988f, 1.0f };
		m_hoverColor = { 0.011f, 0.627f, 0.988f, 1.0f };
		m_clickedColor = { 0.011f, 0.89f, 0.988f, 1.0f };

		m_currentTextColor = m_baseTextColor = m_hoverTextColor = m_clickedTextColor = glm::vec4(1.0f);
	}

	void PushButton::SetPosition(glm::ivec2 pos)
	{
		m_position = pos;
		const glm::ivec2& textSize = m_text->GetSize();
		m_text->SetPosition({ m_position.x - (textSize.x / 2), m_position.y + (textSize.y / 2) });
	}

	void PushButton::SetSize(glm::ivec2 size)
	{
		m_size = size;
		const glm::ivec2& textSize = m_text->GetSize();
		m_text->SetPosition({ m_position.x - (textSize.x / 2), m_position.y + (textSize.y / 2) });
	}

	void PushButton::SetText(std::string_view text) 
	{ 
		m_text->SetText(text); 
		const glm::ivec2& textSize = m_text->GetSize();
		m_text->SetPosition({ m_position.x - (textSize.x / 2), m_position.y + (textSize.y / 2) });
	}

	void PushButton::SetTextColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentTextColor = m_baseTextColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverTextColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedTextColor = color;
	}

	void PushButton::Update(float deltaTime)
	{
		static bool isButtonHeld = false;
		if (this->IsCursorHovering())
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
			{
				m_currentColor = m_clickedColor;
				m_currentTextColor = m_clickedTextColor;
				m_currentBorderColor = m_clickedBorderColor;

				// A button click can span several frames, so prevent the click callback function from being repeatedly called
				if (m_onClickCallbackFunc && !isButtonHeld)
					m_onClickCallbackFunc();

				isButtonHeld = true;
			}
			else
			{
				if (isButtonHeld)
				{
					m_currentColor = m_hoverColor;
					m_currentTextColor = m_hoverTextColor;
					m_currentBorderColor = m_hoverBorderColor;
				}
				else
				{
					m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_baseColor, m_hoverColor, 8.0f, deltaTime);
					m_currentTextColor = FadeTo<glm::vec4>(m_currentTextColor, m_baseTextColor, m_hoverTextColor, 8.0f, deltaTime);
					m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_baseBorderColor, m_hoverBorderColor, 8.0f, deltaTime);
				}

				isButtonHeld = false;
			}
		}
		else
		{
			m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_hoverColor, m_baseColor, 8.0f, deltaTime);
			m_currentTextColor = FadeTo<glm::vec4>(m_currentTextColor, m_hoverTextColor, m_baseTextColor, 8.0f, deltaTime);
			m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_hoverBorderColor, m_baseBorderColor, 8.0f, deltaTime);
		}

		m_text->SetTextColor(m_currentTextColor);
		m_text->Update(deltaTime);
	}

	void PushButton::Render(const Viewport& viewport) const
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

		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/// Render the rest of the button ///
		// Construct the model matrix
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_size, 0.0f });

		// Setup the required shader uniforms
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("color", m_currentColor);

		// Render the button component
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		// Render the text
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);

		m_text->Render(viewport);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
	}

	const std::string& PushButton::GetText() const { return m_text->GetText(); }

	const glm::vec4& PushButton::GetTextColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseTextColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverTextColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedTextColor;
		}

		return m_baseTextColor;
	}
}