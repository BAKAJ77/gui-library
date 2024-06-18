#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <components/button.h>
#include <components/label.h>

namespace GUILib
{
	/**
	* @brief This is a component class for handling and displaying push buttons.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC PushButton : public Button
	{
	public:
		/**
		* @brief The class constructor, sets up the push button component.
		* 
		* @param[in] text - The text displayed on the button.
		* @param[in] font - The font of the text displayed.
		* @param[in] fontSize - The font size of the text displayed.
		*/
		PushButton(std::string_view text, const Font* font, float fontSize);

		~PushButton();

		/**
		* @brief Sets the current position of the push button component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current size of the push button component.
		* @param[in] size - The new size of the component.
		*/
		void SetSize(glm::ivec2 size);

		/**
		* @brief Sets the text to display in the push button component.
		* @param[in] text - The text to be assigned to the push button.
		*/
		void SetText(std::string_view text);

		/**
		* @brief Sets the push button text color to be displayed when the specified component event occurs.
		* @param[in] color - The new text color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the push button text to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetTextColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Updates the logic of the push button component.
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the push button component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns the text displayed in the push button component.
		* @return The string of text which the button component displays.
		*/
		const std::string& GetText() const;

		/**
		* @brief Returns the push button text color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		* 
		* @return The push button text color attached to the specified event.
		*/
		const glm::vec4& GetTextColor(ComponentEvent eventEnum) const;
	protected:
		/**
		* @brief Initialises the push button component.
		*/
		virtual void InitializeComponent() override;
	private:
		glm::vec4 m_baseTextColor, m_hoverTextColor, m_clickedTextColor, m_currentTextColor;
		Label* m_text;
	};
}

#endif