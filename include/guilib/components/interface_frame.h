#ifndef INTERFACE_FRAME_H
#define INTERFACE_FRAME_H

#include <graphics/viewport.h>
#include <components/focusable_component.h>
#include <utilities/timer.h>
#include <unordered_map>
#include <string>

typedef void* (*GLADloadproc)(const char* name);

namespace GUILib
{
	/* 
	* @brief This is a class that represents the root of the user interface, it contains and manages all the user interface elements inside of it.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC InterfaceFrame
	{
	public:
		/**
		* @brief This is the default class constructor method.
		* The viewport is set to default, refer to @ref GUILib::Viewport for more information.
		*/
		InterfaceFrame();

		/**
		* @brief This is a class constructor method.
		* @param[in] viewport - The viewport to be assigned to the interface frame.
		*/
		InterfaceFrame(Viewport viewport);

		/**
		* @brief This is the class move contructor method.
		* @param[in] temp - A temporary InterfaceFrame object.
		*/
		InterfaceFrame(InterfaceFrame&& temp) noexcept;

		InterfaceFrame(const InterfaceFrame&) = delete;
		
		/**
		* @brief The UI components attached are cleaned up automatically by this destructor. 
		*/
		~InterfaceFrame();

		/**
		* @brief Adds UI component to the interface frame.
		* 
		* @param[in] id - The ID to be assigned to the newly added UI component.
		* @param[in] node - The UI component to be added to the interface frame.
		*/
		void AddComponent(std::string_view id, Component* node);

		/**
		* @brief Removes the specified UI component in the interface frame.
		* @param[in] id - The ID of the UI component to be removed.
		*/
		void RemoveComponent(std::string_view id);

		/** 
		* @brief Sets whether or not the interface frame is enabled.
		* If disabled, then it will not be updated and rendered.
		* 
		* @param[in] enabled - The new enable state of the interface frame.
		*/
		void SetEnabled(bool enabled);

		/**
		* @brief Sets the background color of the user interface.
		* @param[in] color - The new color of the UI background.
		*/
		void SetBackgroundColor(glm::vec4 color);

		/**
		* @brief Forces the given component to be set as focused.
		* Any other component which was previously in focus will be set to unfocused.
		* 
		* @param[in] component - The component to be set as focused.
		*/
		void ForceSetCurrentFocused(FocusableComponent* component);
			
		/**
		* @brief Updates the viewport and every enabled user interface component within the interface frame.
		*/
		void Update();

		/**
		* @brief Renders every enabled user interface component within the interface frame.
		*/
		void Render() const;

		/**
		* @brief Returns the specified UI component.
		* 
		* @param[in] id - The ID of the UI component to be looked up.
		* @return A pointer to the UI component identified by the given ID, however if the UI component specfied doesn't exist then 
		* nullptr is returned.
		*/
		Component* GetComponent(std::string_view id);

		/**
		* @brief Returns the specified UI component.
		*
		* @param[in] id - The ID of the UI component to be looked up.
		* @return A pointer to the UI component identified by the given ID, however if the UI component specfied doesn't exist then
		* nullptr is returned.
		*/
		const Component* GetComponent(std::string_view id) const;

		/**
		* @brief Returns the background color of the user interface.
		* @return The color of the UI background.
		*/
		const glm::vec4& GetBackgroundColor() const;

		/**
		* @brief Returns the viewport assigned to the interface frame.
		* @return The viewport of the interface frame.
		*/
		Viewport& GetViewport();

		/**
		* @brief Returns the viewport assigned to the interface frame.
		* @return The viewport of the interface frame.
		*/
		const Viewport& GetViewport() const;

		/**
		* @brief This is the move assignment overload method.
		* @param[in] temp - A temporary InterfaceFrame object.
		* @return A reference to this InterfaceFrame object.
		*/
		const InterfaceFrame& operator=(InterfaceFrame&& temp) noexcept;

		const InterfaceFrame& operator=(const InterfaceFrame&) = delete;
	private:
		Viewport m_viewport;
		glm::vec4 m_bkgColor;
		std::unordered_map<std::string, Component*> m_components;
		Timer m_deltaTimeClock;

		bool m_isEnabled;
	};
}

#endif
