#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <components/focusable_component.h>
#include <components/label.h>
#include <graphics/font.h>
#include <utilities/timer.h>

namespace GUILib
{
	/**
	* @brief This is a component class for handling and displaying textboxes.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC TextBox : public FocusableComponent
	{
	public:
		/**
		* @brief The class constructor, sets up the textbox component.
		*
		* @param[in] font - The font of the hint and input text displayed.
		* @param[in] fontSize - The font size of the hint and input text displayed.
		* @param[in] hintText - The hint text displayed in the text box.
		* @param[in] textCentered - Specifies whether to align the text in the centre, or on the left (default).
		*/
		TextBox(const Font* font, float fontSize, std::string_view hintText = "", bool textCentered = false);

		~TextBox();

		/**
		* @brief Sets whether or not user input is enabled for this textbox component.
		* If enabled, then the textbox will listen for keyboard input.
		* If disabled, then the textbox will not listen for any keyboard input, hence becoming read-only.
		* 
		* @param[in] enabled - Specifies whether or not input is enabled.
		*/
		void SetInputState(bool enabled);

		/** 
		* @brief Sets whether or not the input should be visible.
		* If set to FALSE, then input will be obscured by displaying star characters instead.
		* 
		* @param[in] visible - The new visibility of the inputted text.
		*/
		void SetInputVisibility(bool visible);

		/**
		* @brief Sets the current position of the textbox component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current size of the textbox component.
		* @param[in] pos - The new size of the component.
		*/
		void SetSize(glm::ivec2 size);

		/**
		* @brief Sets the hint text to display in the textbox component.
		* @param[in] text - The hint text to be assigned to the textbox.
		*/
		void SetHintText(std::string_view text);

		/**
		* @brief Sets the textbox component's input text.
		* @param[in] text - The input text to be assigned to the textbox.
		*/
		void SetInputText(std::string_view text);

		/**
		* @brief Sets the textbox field color to be displayed when the specified component event occurs.
		* @param[in] color - The new color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the textbox field to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the textbox field hint text color to be displayed when the specified component event occurs.
		* @param[in] color - The new text color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the textbox field hint text to become the color assigned.
		* The accepted enum values are: NO_EVENT and HOVERED_EVENT.
		*/
		void SetHintTextColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the textbox field input text color to be displayed when the specified component event occurs.
		* @param[in] color - The new text color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the textbox field input text to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetInputTextColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the textbox border color to be displayed when the specified component event occurs.
		* @param[in] color - The new border color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the textbox border to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetBorderColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the border thickness of this textbox component.
		* @param[in] thickness - The new border thickness of the component.
		*/
		void SetBorderThickness(int thickness);

		/**
		* @brief Updates the logic of the textbox component.
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the textbox component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns the current position of the textbox component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the size of this textbox component.
		* @return The size of this component.
		*/
		const glm::ivec2& GetSize() const;

		/**
		* @brief Returns the hint text displayed in the textbox component.
		* @return The textbox's hint text.
		*/
		const std::string& GetHintText() const;

		/**
		* @brief Returns the input text contained in the textbox component.
		* @return The text inputted into the textbox
		*/
		const std::string& GetInputText() const;

		/**
		* @brief Returns the textbox field color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		* 
		* @return The textbox field color attached to the specified event.
		*/
		const glm::vec4& GetColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the textbox field hint text color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT and HOVERED_EVENT.
		* 
		* @return The textbox field hint text color attached to the specified event.
		*/
		const glm::vec4& GetHintTextColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the textbox field input text color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		* 
		* @return The textbox field input text color attached to the specified event.
		*/
		const glm::vec4& GetInputTextColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the textbox field border color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		* 
		* @return The textbox field border color attached to the specified event.
		*/
		const glm::vec4& GetBorderColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the thickness of the textbox component's border.
		* @return The border thickness of the textbox.
		*/
		const int& GetBorderThickness() const;
	protected:
		/**
		* @brief Initialises the textbox component.
		*/
		void InitializeComponent() override;

		/**
		* @brief Checks if the cursor is hovering on the textbox.
		* @return TRUE if cursor is hovering on textbox, FALSE otherwise.
		*/
		bool IsCursorHovering() const;
	private:
		glm::ivec2 m_position, m_size;
		glm::vec4 m_baseColor, m_hoverColor, m_clickedColor, m_currentColor;
		glm::vec4 m_baseHintTextColor, m_hoverHintTextColor, m_currentHintTextColor;
		glm::vec4 m_baseInputTextColor, m_hoverInputTextColor, m_clickedInputTextColor, m_currentInputTextColor;
		glm::vec4 m_baseBorderColor, m_hoverBorderColor, m_clickedBorderColor, m_currentBorderColor;

		int m_borderThickness;

		std::string m_obscuredInputText;
		Label* m_hintText, *m_inputText;
		Timer m_backspaceTimer;

		bool m_inputEnabled, m_isInputVisible, m_textCentered;
	};
}

#endif