#include <components/button.h>
#include <utilities/input_system.h>

namespace GUILib
{
	Button::Button() { this->InitializeComponent(); }
	
	void Button::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Square");

		m_position = m_size = { 0, 0 };
		m_currentBorderColor = m_baseBorderColor = m_hoverBorderColor = m_clickedBorderColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_borderThickness = 4;
	}

	void Button::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void Button::SetSize(glm::ivec2 size) { m_size = size; }

	void Button::SetColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if (eventEnum & ComponentEvent::NO_EVENT)
			m_currentColor = m_baseColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedColor = color;
	}

	void Button::SetBorderColor(glm::vec4 color, ComponentEvent eventEnum)
	{
		if(eventEnum & ComponentEvent::NO_EVENT)
			m_currentBorderColor = m_baseBorderColor = color;
		if (eventEnum & ComponentEvent::HOVERED_EVENT)
			m_hoverBorderColor = color;
		if (eventEnum & ComponentEvent::CLICKED_EVENT)
			m_clickedBorderColor = color;
	}

	void Button::SetBorderThickness(int thickness) { m_borderThickness = thickness; }

	void Button::SetClickCallback(std::function<void()> callbackFunc) { m_onClickCallbackFunc = callbackFunc; }

	bool Button::IsCursorHovering() const
	{
		const glm::vec2 cursorPosition = InputSystem::GetInstance().GetCursorPosition();

		return
			cursorPosition.x >= m_position.x - (m_size.x / 2.0f) && cursorPosition.x <= m_position.x + (m_size.x / 2.0f) &&
			cursorPosition.y >= m_position.y - (m_size.y / 2.0f) && cursorPosition.y <= m_position.y + (m_size.y / 2.0f);
	}

	const glm::ivec2& Button::GetPosition() const { return m_position; }

	const glm::ivec2& Button::GetSize() const { return m_size; }

	const glm::vec4& Button::GetColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedColor;
		}

		return m_baseColor;
	}

	const glm::vec4& Button::GetBorderColor(ComponentEvent eventEnum) const
	{
		switch (eventEnum)
		{
		case ComponentEvent::NO_EVENT: return m_baseBorderColor;
		case ComponentEvent::HOVERED_EVENT: return m_hoverBorderColor;
		case ComponentEvent::CLICKED_EVENT: return m_clickedBorderColor;
		}

		return m_baseBorderColor;
	}

	const int& Button::GetBorderThickness() const { return m_borderThickness; }
}
