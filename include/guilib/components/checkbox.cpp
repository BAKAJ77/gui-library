#include <components/checkbox.h>
#include <graphics/animation.h>
#include <utilities/input_system.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	Checkbox::Checkbox() : 
		m_isChecked(false)
	{ 
		this->InitializeComponent(); 
	}

	void Checkbox::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Square");
		m_checkmarkGeometry = *ResourceLoader::GetInstance().GetGeometry("Checkmark");

		m_position = { 0, 0 };
		m_scale = 30;

		m_currentColor = m_baseColor = { 0.6f, 0.6, 0.6f, 1.0f };
		m_hoverColor = { 0.8f, 0.8f, 0.8f, 1.0f };
		m_clickedColor = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_currentBorderColor = m_baseBorderColor = m_hoverBorderColor = m_clickedBorderColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_borderThickness = 4;

		m_checkmarkColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	void Checkbox::SetCheckedState(bool checked) { m_isChecked = checked; }

	void Checkbox::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void Checkbox::SetScaleSize(int scale) { m_scale = scale; }

	void Checkbox::SetColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentColor = m_baseColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedColor = color;
	}

	void Checkbox::SetBorderColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentBorderColor = m_baseBorderColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverBorderColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedBorderColor = color;
	}

	void Checkbox::SetBorderThickness(int thickness) { m_borderThickness = thickness; }

	void Checkbox::SetCheckmarkColor(glm::vec4 color) { m_checkmarkColor = color; }

	bool Checkbox::IsCursorHovering() const
	{
		const glm::vec2 cursorPosition = InputSystem::GetInstance().GetCursorPosition();

		return
			cursorPosition.x >= m_position.x - (m_scale / 2.0f) && cursorPosition.x <= m_position.x + (m_scale / 2.0f) &&
			cursorPosition.y >= m_position.y - (m_scale / 2.0f) && cursorPosition.y <= m_position.y + (m_scale / 2.0f);
	}

	void Checkbox::Update(float deltaTime)
	{
		static bool isButtonHeld = false;
		if (this->IsCursorHovering())
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
			{
				m_currentColor = m_clickedColor;
				m_currentBorderColor = m_clickedBorderColor;

				// A button click can span several frames, so prevent the repeatedly checked switches
				if (!isButtonHeld)
					m_isChecked = !m_isChecked;

				isButtonHeld = true;
			}
			else
			{
				if (isButtonHeld)
				{
					m_currentColor = m_hoverColor;
					m_currentBorderColor = m_hoverBorderColor;
				}
				else
				{
					m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_baseColor, m_hoverColor, 8.0f, deltaTime);
					m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_baseBorderColor, m_hoverBorderColor, 8.0f, deltaTime);
				}

				isButtonHeld = false;
			}
		}
		else
		{
			m_currentColor = FadeTo<glm::vec4>(m_currentColor, m_hoverColor, m_baseColor, 8.0f, deltaTime);
			m_currentBorderColor = FadeTo<glm::vec4>(m_currentBorderColor, m_hoverBorderColor, m_baseBorderColor, 8.0f, deltaTime);
		}
	}

	void Checkbox::Render(const Viewport& viewport) const
	{
		/// Render the border first ///
		// Construct the model matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_scale + m_borderThickness, m_scale + m_borderThickness, 0.0f });

		// Bind the shader and setup the shader uniforms
		m_shaders->Bind();
		m_shaders->SetUniform("textureSampler", 0);
		m_shaders->SetUniform("useTextures", false);
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
		m_shaders->SetUniformGLM("color", m_currentBorderColor);

		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/// Render the rest of the checkbox ///
		// Construct the model matrix
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_scale, m_scale, 0.0f });

		// Setup the required shader uniforms
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("color", m_currentColor);

		// Render the checkbox
		m_geometry.vao->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (m_isChecked) // Render the checkmark if the checkbox is checked
		{
			// Construct the model matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
			modelMatrix = glm::scale(modelMatrix, { m_scale - 7, m_scale - 7, 0.0f });
			
			// Setup the required shader uniforms
			m_shaders->SetUniformGLM("model", modelMatrix);
			m_shaders->SetUniformGLM("color", m_checkmarkColor);

			// Render the checkmark
			m_checkmarkGeometry.vao->Bind();
			glLineWidth(6.0f);
			glDrawArrays(GL_LINES, 0, 4);
			glLineWidth(1.0f);
		}
	}

	bool Checkbox::IsChecked() const { return m_isChecked; }

	const glm::ivec2& Checkbox::GetPosition() const { return m_position; }

	const int& Checkbox::GetScaleSize() const { return m_scale; }

	const glm::vec4& Checkbox::GetColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedColor;
		}

		return m_baseColor;
	}

	const glm::vec4& Checkbox::GetBorderColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseBorderColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverBorderColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedBorderColor;
		}

		return m_baseBorderColor;
	}

	const glm::vec4& Checkbox::GetCheckmarkColor() const { return m_checkmarkColor; }

	const int& Checkbox::GetBorderThickness() const { return m_borderThickness; }
}
