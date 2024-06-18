#include <components/radio_button.h>
#include <graphics/animation.h>
#include <utilities/input_system.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	RadioButton::RadioButton() :
		m_isSelected(false), m_clicked(false)
	{
		this->InitializeComponent();
	}

	void RadioButton::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Circle");
		
		m_position = { 0, 0 };
		m_diameter = 30;

		m_currentColor = m_baseColor = { 0.6f, 0.6, 0.6f, 1.0f };
		m_hoverColor = { 0.8f, 0.8f, 0.8f, 1.0f };
		m_clickedColor = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_currentBorderColor = m_baseBorderColor = m_hoverBorderColor = m_clickedBorderColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_borderThickness = 4;

		m_dotMarkColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	void RadioButton::SetSelected(bool selected) { m_isSelected = selected; }

	void RadioButton::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void RadioButton::SetDiameter(int diameter) { m_diameter = diameter; }

	void RadioButton::SetColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentColor = m_baseColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedColor = color;
	}

	void RadioButton::SetBorderColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentBorderColor = m_baseBorderColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverBorderColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedBorderColor = color;
	}

	void RadioButton::SetBorderThickness(int thickness) { m_borderThickness = thickness; }

	void RadioButton::SetDotMarkColor(glm::vec4 color) { m_dotMarkColor = color; }

	bool RadioButton::IsCursorHovering() const
	{
		const glm::ivec2& cursorPosition = InputSystem::GetInstance().GetCursorPosition();
		const glm::vec2 difference = m_position - cursorPosition;
		
		return glm::length(difference) <= (m_diameter / 2.0f);
	}

	void RadioButton::Update(float deltaTime)
	{
		static bool isButtonHeld = false;
		m_clicked = false;

		if (this->IsCursorHovering())
		{
			if (InputSystem::GetInstance().WasMouseButtonPressed(MouseButtonCode::MOUSE_BUTTON_LEFT))
			{
				m_currentColor = m_clickedColor;
				m_currentBorderColor = m_clickedBorderColor;

				// A button click can span several frames, so prevent the repeatedly checked switches
				if (!isButtonHeld)
					m_clicked = true;

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

	void RadioButton::Render(const Viewport& viewport) const
	{
		/// Render the border first ///
		// Construct the model matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_diameter + m_borderThickness, m_diameter + m_borderThickness, 0.0f });

		// Bind the shader and setup the shader uniforms
		m_shaders->Bind();
		m_shaders->SetUniform("useTextures", false);
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
		m_shaders->SetUniformGLM("color", m_currentBorderColor);

		m_geometry.vao->Bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, (int)(360.0f / ResourceConstants::circleGeoemtryAngleStep) + 2);

		/// Render the rest of the radio button ///
		// Construct the model matrix
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
		modelMatrix = glm::scale(modelMatrix, { m_diameter, m_diameter, 0.0f });

		// Setup the required shader uniforms
		m_shaders->SetUniformGLM("model", modelMatrix);
		m_shaders->SetUniformGLM("color", m_currentColor);

		// Render the checkbox
		m_geometry.vao->Bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, (int)(360.0f / ResourceConstants::circleGeoemtryAngleStep) + 2);

		if (m_isSelected) // Render the dot mark if the radio button is selected
		{
			// Construct the model matrix
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
			modelMatrix = glm::scale(modelMatrix, { m_diameter - 15, m_diameter - 15, 0.0f });

			// Setup the required shader uniforms
			m_shaders->SetUniformGLM("model", modelMatrix);
			m_shaders->SetUniformGLM("color", m_dotMarkColor);

			m_geometry.vao->Bind();
			glDrawArrays(GL_TRIANGLE_FAN, 0, (int)(360.0f / ResourceConstants::circleGeoemtryAngleStep) + 2);
		}
	}

	bool RadioButton::IsSelected() const { return m_isSelected; }

	bool RadioButton::WasClicked() const { return m_clicked; }

	const glm::ivec2& RadioButton::GetPosition() const { return m_position; }

	const int& RadioButton::GetDiameter() const { return m_diameter; }

	const glm::vec4& RadioButton::GetColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedColor;
		}

		return m_baseColor;
	}

	const glm::vec4& RadioButton::GetBorderColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseBorderColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverBorderColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedBorderColor;
		}

		return m_baseBorderColor;
	}

	const int& RadioButton::GetBorderThickness() const { return m_borderThickness; }

	const glm::vec4& RadioButton::GetDotMarkColor() const { return m_dotMarkColor; }
}
