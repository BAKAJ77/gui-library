#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <components/component.h>

namespace GUILib
{
	/**
	* @brief This is a component class for handling and displaying checkboxes.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC Checkbox : public Component
	{
	public:
		/**
		* @brief This is the default class constructor.
		*/
		Checkbox();

		~Checkbox() = default;

		/**
		* @brief Sets whether the checkbox is checked or not.
		* @param[in] checked - The new checked state of the checkbox component.
		*/
		void SetCheckedState(bool checked);

		/**
		* @brief Sets the current position of the checkbox component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current scale size of the checkbox component.
		* @param[in] size - The new x and y scale size of the component.
		*/
		void SetScaleSize(int scale);

		/**
		* @brief Sets the checkbox color to be displayed when the specified component event occurs.
		* @param[in] color - The new color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetColor(glm::vec4 color, ComponentEvent eventEnum);


		/**
		* @brief Sets the checkbox border color to be displayed when the specified component event occurs.
		* @param[in] color - The new border color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button border to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetBorderColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the border thickness of this checkbox component.
		* @param[in] thickness - The new border thickness of the component.
		*/
		void SetBorderThickness(int thickness);

		/**
		* @brief Sets the color of the checkmark.
		* @param[in] color - The new color of the checkmark.
		*/
		void SetCheckmarkColor(glm::vec4 color);

		/**
		* @brief Updates the logic of the checkbox component.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the checkbox component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns whether or not the checkbox is currently checked.
		* @return TRUE if checked, FALSE otherwise.
		*/
		bool IsChecked() const;

		/**
		* @brief Returns the current position of the checkbox component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the scale size of the checkbox component.
		* @return The scale size of this component.
		*/
		const int& GetScaleSize() const;

		/**
		* @brief Returns the checkbox color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The checkbox color attached to the specified event.
		*/
		const glm::vec4& GetColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the checkbox border color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The checkbox border color attached to the specified event.
		*/
		const glm::vec4& GetBorderColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the thickness of the checkbox component's border.
		* @return The border thickness of the checkbox.
		*/
		const int& GetBorderThickness() const;

		/**
		* @brief Returns the color of the checkmark.
		* @return The checkmark color.
		*/
		const glm::vec4& GetCheckmarkColor() const;
	protected:
		/**
		* @brief Initialises the checkbox component.
		*/
		void InitializeComponent() override;

		/**
		* @brief Checks if the cursor is hovering on the checkbox.
		* @return TRUE if cursor is hovering on checkbox, FALSE otherwise.
		*/
		bool IsCursorHovering() const;
	protected:
		ResourceLoader::Geometry m_checkmarkGeometry;

		glm::ivec2 m_position;
		glm::vec4 m_baseColor, m_hoverColor, m_clickedColor, m_currentColor;
		glm::vec4 m_baseBorderColor, m_hoverBorderColor, m_clickedBorderColor, m_currentBorderColor;
		glm::vec4 m_checkmarkColor;
		int m_scale, m_borderThickness;

		bool m_isChecked;
	};
}

#endif
