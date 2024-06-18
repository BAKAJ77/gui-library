#ifndef FOCUSABLE_COMPONENT_H
#define FOCUSABLE_COMPONENT_H

#include <components/component.h>

namespace GUILib
{
	/**
	* @brief This is an pure virtual class representing a base for deriving focusable UI components.
	*/
	class LIB_DECLSPEC FocusableComponent : public Component
	{
	public:
		/**
		* @brief This is the default class constructor.
		*/
		FocusableComponent();

		virtual ~FocusableComponent() = default;

		/**
		* @brief Sets whether or not the component is focused.
		* @param[in] state - The new focus state of the component.
		*/
		void SetFocusState(bool state);

		/**
		* @brief Updates the logic of the UI component.
		* This is required to be overrided by deriving focusable UI component classes.
		* 
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		virtual void Update(float deltaTime) override = 0;

		/**
		* @brief Renders the UI component.
		* This is required to be overrided by deriving focusable UI component classes.
		* @param[in] viewport - The viewport where the UI component will be rendered.
		*/
		virtual void Render(const Viewport& viewport) const override = 0;

		/**
		* @brief Returns whether or not the component is in focus.
		* @return TRUE if focused, FALSE otherwise.
		*/
		bool IsFocused() const;

		/**
		* @brief Returns whether or not the component has requested focus.
		* @return TRUE if focus has been requested, FALSE otherwise.
		*/
		bool HasRequestedFocus() const;
	protected:
		/**
		* @brief Initialises the UI component.
		*/
		virtual void InitializeComponent() override = 0;

		/**
		* @brief Resets the gained and lost focus flags back to FALSE.
		*/
		void ResetActionFocusFlags();
	protected:
		bool m_isFocused, m_requestedFocus, m_gainedFocus, m_lostFocus;
	};
}

#endif