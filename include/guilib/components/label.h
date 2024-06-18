#ifndef LABEL_H
#define LABEL_H

#include <components/component.h>
#include <graphics/font.h>

namespace GUILib
{
	/**
	* @brief This is a component class for displaying text labels.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC Label : public Component
	{
	public:
		/**
		* @brief This is a class constructor for assigning text attributes to the label component.
		* 
		* @param[in] text - A string of text to assign to the label.
		* @param[in] color - The color of the text displayed by the label.
		* @param[in] font - The font to assign to the label.
		* @param[in] fontSize - The size of the text font (in pixels).
		*/
		Label(std::string_view text, glm::vec4 color, const Font* font, float fontSize);

		~Label() = default;

		/**
		* @brief Sets the current position of the label component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the font of the label component.
		* @param[in] font - The font to be assigned to the label.
		*/
		void SetFont(const Font* font);

		/**
		* @brief Sets the font size of the label component.
		* @param[in] size - The size of the font assigned to the label (in pixels).
		*/
		void SetFontSize(float size);

		/**
		* @brief Sets the text which the label component will display.
		* @param[in] text - The text to be assigned to the label.
		*/
		void SetText(std::string_view text);

		/**
		* @brief Sets the current text color of the label component.
		* @param[in] color - The new color of the text.
		*/
		void SetTextColor(glm::vec4 color);

		/**
		* @brief Updates the logic of the label component.
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the label component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns the current position of the label component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the font assigned to the label component.
		* @return A pointer to the font assigned to the label.
		*/
		const Font* GetFont() const;

		/**
		* @brief Returns the font size assigned to the label component.
		* @return The label's font size.
		*/
		const float GetFontSize() const;

		/**
		* @brief Returns the text displayed by the label component.
		* @return A string of text which the label component displays.
		*/
		const std::string& GetText() const;

		/**
		* @brief Returns the text color of this label component.
		* @return The label's text color.
		*/
		const glm::vec4& GetTextColor() const;

		/**
		* @brief Returns the size of this label component.
		* @return The size of this component.
		*/
		const glm::ivec2& GetSize() const;
	private:
		/**
		* @brief An enumeration specifying the data which should be updated.
		*/
		enum class UpdateFlags { NONE, UPDATE_GEOMETRY_DATA, UPDATE_TEXT_SIZE_DATA, UPDATE_ALL };

		/**
		* @brief Initialises the label component.
		*/
		void InitializeComponent() override;

		/**
		* @brief Generates the geometry data required to display the text.
		*/
		void GenerateTextGeometry();

		/**
		* @brief Calculates the size (in pixels) of the text string when displayed.
		* @return A two-dimensional vector representing the size of the text.
		*/
		glm::ivec2 CalculateTextSize() const;
	private:
		// Private component attributes
		mutable glm::ivec2 m_position, m_size;
		glm::vec4 m_textColor;
		std::string m_text;
		const Font* m_font;
		float m_fontSize;

		// Flags
		mutable UpdateFlags m_shouldUpdate;
		bool m_textLengthChanged;
	};
}

#endif