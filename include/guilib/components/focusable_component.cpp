#include <components/focusable_component.h>

namespace GUILib
{
	FocusableComponent::FocusableComponent() :
		m_isFocused(false), m_requestedFocus(false), m_gainedFocus(false), m_lostFocus(false)
	{}

	void FocusableComponent::SetFocusState(bool state)
	{
		if (m_requestedFocus && state)
			m_requestedFocus = false;

		if (!m_isFocused && state)
			m_gainedFocus = true;
		else if (m_isFocused && !state)
			m_lostFocus = true;

		m_isFocused = state;
	}

	void FocusableComponent::ResetActionFocusFlags() { m_gainedFocus = m_lostFocus = false; }

	bool FocusableComponent::IsFocused() const { return m_isFocused; }

	bool FocusableComponent::HasRequestedFocus() const { return m_requestedFocus; }
}