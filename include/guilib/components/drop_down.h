#ifndef DROP_DOWN_H
#define DROP_DOWN_H

#include <components/focusable_component.h>
#include <components/push_button.h>
#include <components/textbox.h>
#include <vector>

namespace GUILib
{
	class LIB_DECLSPEC DropDown : public FocusableComponent
	{
	public:
		/** 
		* @brief The class constructor which initializes the drop-down component.
		* 
		* @param[in] viewport - The viewport which the component will be rendered to.
		* @param[in] font - The font to be used by the component to display text.
		* @param[in] fontSize - The font size of text displayed in the component.
		*/
		DropDown(const Viewport& viewport, const Font* font, float fontSize);

		~DropDown();

		/**
		* @brief Adds new option to the drop-down component.
		* 
		* @param[in] optionText - The text displayed when the option is viewed in the drop-down.
		* @param[in] valueID - The ID value identifying the option. The value given must be larger than 0.
		*/
		void AddOption(std::string_view optionText, int valueID);

		/**
		* @brief Removes the specified option from the drop-down component.
		* @param[in] valueID - The ID value of the option to be removed.
		*/
		void RemoveOption(int valueID);

		/**
		* @brief Removes all existing options in the drop-down component.
		*/
		void ClearSelectionList();

		/**
		* @brief Sets the current selection option in the drop-down component.
		* @param[in] valueID - The ID value of the option to be set current. If the valueID given is < 0, then current selected will be set
		* to null, no option will be current selected.
		*/
		void SetCurrentSelected(int valueID);

		/**
		* @brief Sets the current position of the drop-down component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current size of the drop-down component.
		* @param[in] pos - The new size of the component.
		*/
		void SetSize(glm::ivec2 size);

		/**
		* @brief Sets the drop-down color to be displayed when the specified component event occurs.
		* @param[in] color - The new color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the drop-down to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the drop-down border color to be displayed when the specified component event occurs.
		* @param[in] color - The new border color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the drop-down border to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetBorderColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the border thickness of this drop-down component.
		* @param[in] thickness - The new border thickness of the component.
		*/
		void SetBorderThickness(int thickness);

		/**
		* @brief Sets the color of the line seperators in the drop-down component.
		* @param[in] color - The new seperator color to be assigned.
		*/
		void SetSeperatorColor(glm::vec4 color);

		/**
		* @brief Updates the logic of the drop-down component.
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the drop-down component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		 * @brief Returns the current selection drop-down option.
		 * @return The value ID of the selected option.
		 */
		int GetSelectedOption() const;

		/**
		* @brief Returns the current position of the drop-down component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the size of this drop-down component.
		* @return The size of this component.
		*/
		const glm::ivec2& GetSize() const;

		/**
		* @brief Returns the drop-down color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The drop-down color attached to the specified event.
		*/
		const glm::vec4& GetColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the drop-down border color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The drop-down border color attached to the specified event.
		*/
		const glm::vec4& GetBorderColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the thickness of the drop-down component's border.
		* @return The border thickness of the drop-down.
		*/
		const int& GetBorderThickness() const;

		/**
		* @brief Returns the color of the drop-down component's line seperators.
		* @return The color of the component's line seperators.
		*/
		const glm::vec4& GetSeperatorColor() const;
	private:
		struct SelectionOption
		{
			PushButton* button = nullptr;
			int valueID = -1;
		};

		/**
		* @brief Initialises the drop-down component.
		*/
		void InitializeComponent() override;

		/**
		* @brief Calculates the max amount of options can be displayed at one time by the drop-down component.
		* 
		* @param[in] viewport - The viewport which the component is being rendered to.
		* @return The max amount of options visible at one time.
		*/
		int CalculateMaxVisibleOptions(const Viewport& viewport) const;
	private:
		const Font* m_font;
		float m_fontSize;
		glm::vec4 m_seperatorColor;
		
		TextBox* m_currentSelectedBox;
		int m_currentSelectedValueID;

		std::vector<SelectionOption> m_options;
		int m_maxVisibleOptions;
		float m_optionsOffset;

		ResourceLoader::Geometry m_triangleGeometry;
	};
}

#endif