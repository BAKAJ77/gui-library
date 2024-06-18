#include <components/component.h>

namespace GUILib
{
	Component::Component() :
		m_shaders(nullptr), m_isEnabled(true)
	{}

	void Component::SetEnabled(bool enable) { m_isEnabled = enable; }

	bool Component::IsEnabled() const { return m_isEnabled; }
}