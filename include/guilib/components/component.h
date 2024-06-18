#ifndef COMPONENT_H
#define COMPONENT_H

#include <utilities/libexport.h>
#include <utilities/resource_loader.h>
#include <graphics/viewport.h>

namespace GUILib
{
	class ShaderProgram;
	class ResourceLoader::Geometry;

	/**
	* @brief This enumeration is purposed for specifying the component event which a value should be attached to.
	* For example, say you want a button to be a red color when uninteracted with, green when hovered over, and blue when clicked, you would
	* do something like this:
	* 
	* @code	.cpp
	*	button->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f}, ComponentEvent::NO_EVENT); // For red base color
	*	button->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f}, ComponentEvent::HOVERED_EVENT); // For green hovered color
	*	button->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f}, ComponentEvent::CLICKED_EVENT); // For blue clicked color
	*/
	enum class ComponentEvent : int { NO_EVENT = 1, HOVERED_EVENT = 2, CLICKED_EVENT = 4 };

	static inline ComponentEvent operator|(ComponentEvent left, ComponentEvent right)
	{
		return (ComponentEvent)((int)left | (int)right);
	}

	static inline bool operator&(ComponentEvent left, ComponentEvent right)
	{
		return ((int)left & (int)right) == (int)right;
	}

	/**
	* @brief This is an pure virtual class representing a base for deriving UI components.
	*/
	class LIB_DECLSPEC Component
	{
	public:
		/**
		* @brief This is the default class constructor.
		*/
		Component();

		virtual ~Component() = default;

		/**
		* @brief Sets whether or not the component is enabled.
		* @param[in] enable - Represents whether the component should be enabled or disabled.
		*/
		void SetEnabled(bool enable);

		/**
		* @brief Updates the logic of the UI component.
		* This is required to be overrided by deriving UI component classes.
		* 
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		virtual void Update(float deltaTime) = 0;

		/**
		* @brief Renders the UI component.
		* This is required to be overrided by deriving UI component classes.
		* @param[in] viewport - The viewport where the UI component will be rendered.
		*/
		virtual void Render(const Viewport& viewport) const = 0;

		/**
		* @brief Returns whether or not the component is enabled.
		* @return TRUE if the component is enabled, FALSE otherwise.
		*/
		bool IsEnabled() const;
	protected:
		/**
		* @brief Initialises the UI component.
		*/
		virtual void InitializeComponent() = 0;
	protected:
		ShaderProgram* m_shaders;
		ResourceLoader::Geometry m_geometry;
		bool m_isEnabled;
	};
}

#endif