#include <graphics/viewport.h>
#include <external/glad/glad.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	Viewport::Viewport() :
		m_position(0, 0), m_size(600, 600), m_matrix(glm::mat4(1.0f)), m_changed(true)
	{}

	Viewport::Viewport(glm::ivec2 pos, glm::ivec2 size) :
		m_position(pos), m_size(size), m_matrix(glm::mat4(1.0f)), m_changed(true)
	{}

	void Viewport::SetPosition(glm::ivec2 pos) 
	{ 
		m_position = pos; 
		m_changed = true;
	}

	void Viewport::SetSize(glm::ivec2 size) 
	{ 
		m_size = size; 
		m_changed = true;
	}

	void Viewport::Update()
	{
		if (m_changed)
		{
			glViewport(m_position.x, m_position.y, m_size.x, m_size.y);
			m_matrix = glm::ortho(0.0f, (float)m_size.x, (float)m_size.y, 0.0f);
			m_changed = false;
		}
	}

	const glm::mat4& Viewport::GetMatrix() const { return m_matrix; }

	const glm::ivec2& Viewport::GetPosition() const { return m_position; }

	const glm::ivec2& Viewport::GetSize() const { return m_size; }
}