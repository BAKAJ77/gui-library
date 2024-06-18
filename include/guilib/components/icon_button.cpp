#include <components/icon_button.h>
#include <graphics/animation.h>
#include <graphics/buffer_objects.h>
#include <utilities/input_system.h>

#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	IconButton::IconButton(const TextureBuffer2D* texture) :
		m_iconTexture(texture), m_isButtonHeld(false)
	{
		this->InitializeComponent();
		
		// Scale down to 64 pixels in height by default
		const float scaleFactor = 64.0f / texture->GetHeight();
		m_size = { (float)texture->GetWidth() * scaleFactor, (float)texture->GetHeight() * scaleFactor };
	}

	void IconButton::InitializeComponent()
	{
		m_currentColor = m_baseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_hoverColor = { 1.0f, 1.0f, 0.4f, 1.0f };
		m_clickedColor = { 1.0f, 1.0f, 0.0f, 1.0f };
	}

	void IconButton::Update(float deltaTime)
	{
		if (this->IsCursorHovering())
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
			{
				m_currentColor = m_clickedColor;
				m_currentBorderColor = m_clickedBorderColor;

				// A button click can span several frames, so prevent the click callback function from being repeatedly called
				if (m_onClickCallbackFunc && !m_isButtonHeld)
					m_onClickCallbackFunc();

				m_isButtonHeld = true;
			}
			else
			{
				if (m_isButtonHeld)
				{
					m_currentColor = m_hoverColor;
					m_currentBorderColor = m_hoverBorderColor;
				}
				else
				{
					m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_baseColor, m_hoverColor, 8.0f, deltaTime);
					m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_baseBorderColor, m_hoverBorderColor, 8.0f, deltaTime);
				}

				m_isButtonHeld = false;
			}
		}
		else
		{
			m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_hoverColor, m_baseColor, 8.0f, deltaTime);
			m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_hoverBorderColor, m_baseBorderColor, 8.0f, deltaTime);
		}
	}

	void IconButton::Render(const Viewport& viewport) const
	{
		// Construct the model matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_size, 0.0f });

		// Bind the shader and setup the shader uniforms
		m_shaders->Bind();
		m_shaders->SetUniform("textureSampler", 0);
		m_shaders->SetUniform("useTextures", true);
		m_shaders->SetUniform("enableColorMod", true);
		m_shaders->SetUniformGLM("color", m_currentColor);
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());

		// Render the icon button component
		m_geometry.vao->Bind();
		m_iconTexture->Bind(0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}