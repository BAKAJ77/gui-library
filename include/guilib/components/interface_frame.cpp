#include <components/interface_frame.h>
#include <components/focusable_component.h>
#include <utilities/resource_loader.h>
#include <utilities/input_system.h>
#include <external/glad/glad.h>

namespace GUILib
{
	InterfaceFrame::InterfaceFrame() :
		m_bkgColor({ 0.0f, 0.0f, 0.0f, 1.0f }), m_isEnabled(true)
	{}

	InterfaceFrame::InterfaceFrame(Viewport viewport) :
		m_viewport(viewport), m_bkgColor({ 0.0f, 0.0f, 0.0f, 1.0f }), m_isEnabled(true)
	{}

	InterfaceFrame::InterfaceFrame(InterfaceFrame&& temp) noexcept :
		m_viewport(temp.m_viewport), m_bkgColor({ 0.0f, 0.0f, 0.0f, 1.0f }), m_isEnabled(true)
	{}

	InterfaceFrame::~InterfaceFrame()
	{ 
		for (auto& componentPair : m_components)
			delete componentPair.second;
	}

	void InterfaceFrame::AddComponent(std::string_view id, Component* node)
	{
		// Make sure a shader with the specified ID doesn't exist already
		if (m_components.find(id.data()) != m_components.end())
			return;

		// Add the UI component to the unordered map
		m_components.insert({ id.data(), node });
	}

	void InterfaceFrame::RemoveComponent(std::string_view id)
	{
		auto iterator = m_components.find(id.data());
		if (iterator != m_components.end())
			m_components.erase(iterator);
	}

	void InterfaceFrame::SetEnabled(bool enabled) { m_isEnabled = enabled; }

	void InterfaceFrame::SetBackgroundColor(glm::vec4 color) { m_bkgColor = color; }

	void InterfaceFrame::ForceSetCurrentFocused(FocusableComponent* component)
	{
		component->SetFocusState(true);

		for (auto& componentPair : m_components)
		{
			auto* focusable = dynamic_cast<FocusableComponent*>(componentPair.second);
			if (focusable && focusable != component)
				focusable->SetFocusState(false);
		}
	}

	void InterfaceFrame::Update()
	{
		const float deltaTime = m_deltaTimeClock.GetElapsedTime();
		m_deltaTimeClock.Reset();
		m_viewport.Update();

		if (m_isEnabled)
		{
			FocusableComponent* focusChanged = nullptr; // The component which has gained focus
			for (auto& componentPair : m_components)
			{
				// Update each component in the scene
				if (componentPair.second && componentPair.second->IsEnabled())
					componentPair.second->Update(deltaTime);

				// Check if a focusable component is requesting focus (if one hasn't already)
				if (!focusChanged)
				{
					if (auto* focusable = dynamic_cast<FocusableComponent*>(componentPair.second))
					{
						if (focusable->HasRequestedFocus())
						{
							// Set the focusable component's state to focused
							focusable->SetFocusState(true);
							focusChanged = focusable;
						}
					}
				}
			}

			// If focus has been attained by a focusable component, then set all the other focusable components states to unfocused.
			if (focusChanged)
			{
				for (auto& componentPair : m_components)
				{
					if (auto* focusable = dynamic_cast<FocusableComponent*>(componentPair.second))
					{
						if (focusable != focusChanged)
							focusable->SetFocusState(false);
					}
				}
			}
		}
	}

	void InterfaceFrame::Render() const 
	{
		if (m_isEnabled)
		{
			// Clear the window screen
			glClearColor(m_bkgColor.r, m_bkgColor.g, m_bkgColor.b, m_bkgColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// Render all the UI components
			for (const auto& componentPair : m_components)
			{
				if (componentPair.second && componentPair.second->IsEnabled())
					componentPair.second->Render(m_viewport);
			}
		}
	}

	Component* InterfaceFrame::GetComponent(std::string_view id)
	{
		auto iterator = m_components.find(id.data());
		if (iterator != m_components.end())
			return iterator->second;

		return nullptr;
	}

	const Component* InterfaceFrame::GetComponent(std::string_view id) const
	{
		auto iterator = m_components.find(id.data());
		if (iterator != m_components.end())
			return iterator->second;

		return nullptr;
	}

	const glm::vec4& InterfaceFrame::GetBackgroundColor() const { return m_bkgColor; }

	Viewport& InterfaceFrame::GetViewport() { return m_viewport; }

	const Viewport& InterfaceFrame::GetViewport() const { return m_viewport; }

	const InterfaceFrame& InterfaceFrame::operator=(InterfaceFrame&& temp) noexcept
	{
		m_viewport = temp.m_viewport;
		m_components = temp.m_components;
		temp.m_components.clear();
		return *this;
	}
}
