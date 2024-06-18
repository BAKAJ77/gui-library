#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include <components/component.h>

namespace GUILib
{
	/**
	* @brief This is a component class for handling and displaying radio buttons.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC RadioButton : public Component
	{
	public:
		/**
		* @brief This is the default class constructor.
		*/
		RadioButton();

		~RadioButton() = default;

		/**
		* @brief Sets whether the radio button is selected or not.
		* @param[in] selected - Specifies whether the radio button is selected or not.
		*/
		void SetSelected(bool selected);

		/**
		* @brief Sets the current position of the radio button component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current diameter of the radio button component.
		* @param[in] size - The new diameter of the component.
		*/
		void SetDiameter(int diameter);

		/**
		* @brief Sets the radio button color to be displayed when the specified component event occurs.
		* @param[in] color - The new color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetColor(glm::vec4 color, ComponentEvent eventEnum);


		/**
		* @brief Sets the radio button border color to be displayed when the specified component event occurs.
		* @param[in] color - The new border color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button border to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetBorderColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the border thickness of this radio button component.
		* @param[in] thickness - The new border thickness of the component.
		*/
		void SetBorderThickness(int thickness);

		/**
		* @brief Sets the color of the dot mark when the radio button is selected.
		* @param[in] color - The new color of the dot mark.
		*/
		void SetDotMarkColor(glm::vec4 color);

		/**
		* @brief Updates the logic of the radio button component.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the radio button component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns whether or not the radio button is currently selected.
		* @return TRUE if selected, FALSE otherwise.
		*/
		bool IsSelected() const;

		/**
		* @brief Returns whether or not the radio button was clicked.
		* @return TRUE if clicked, FALSE otherwise.
		*/
		bool WasClicked() const;

		/**
		* @brief Returns the current position of the radio button component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the diameter of the radio button component.
		* @return The diameter of this component.
		*/
		const int& GetDiameter() const;

		/**
		* @brief Returns the radio button color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The radio button color attached to the specified event.
		*/
		const glm::vec4& GetColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the radio button border color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The radio button border color attached to the specified event.
		*/
		const glm::vec4& GetBorderColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the thickness of the radio button component's border.
		* @return The border thickness of the radio button.
		*/
		const int& GetBorderThickness() const;

		/**
		* @brief Returns the color of the dot mark when the radio button is selected.
		* @return The radio button dot mark color.
		*/
		const glm::vec4& GetDotMarkColor() const;
	protected:
		/**
		* @brief Initialises the radio button component.
		*/
		void InitializeComponent() override;

		/**
		* @brief Checks if the cursor is hovering on the radio button.
		* @return TRUE if cursor is hovering on radio button, FALSE otherwise.
		*/
		bool IsCursorHovering() const;
	protected:
		glm::ivec2 m_position;
		glm::vec4 m_baseColor, m_hoverColor, m_clickedColor, m_currentColor;
		glm::vec4 m_baseBorderColor, m_hoverBorderColor, m_clickedBorderColor, m_currentBorderColor;
		glm::vec4 m_dotMarkColor;
		int m_diameter, m_borderThickness;

		bool m_isSelected, m_clicked;
	};
}

#endif
