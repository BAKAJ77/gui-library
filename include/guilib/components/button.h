#ifndef BUTTON_H
#define BUTTON_H

#include <components/component.h>

namespace GUILib
{
	/**
	* @brief This is a pure abstract class for button related components to derive from.
	*/
	class LIB_DECLSPEC Button : public Component
	{
	public:
		/**
		* @brief This is the default class constructor.
		*/
		Button();

		virtual ~Button() = default;

		/**
		* @brief Sets the current position of the button component.
		* @param[in] pos - The new position of the component.
		*/
		virtual void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current size of the button component.
		* @param[in] size - The new size of the component.
		*/
		virtual void SetSize(glm::ivec2 size);

		/**
		* @brief Sets the button color to be displayed when the specified component event occurs.
		* @param[in] color - The new color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the button border color to be displayed when the specified component event occurs.
		* @param[in] color - The new border color to be assigned.
		* @param[in] eventEnum - The component event(s) which will trigger the button border to become the color assigned.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*/
		void SetBorderColor(glm::vec4 color, ComponentEvent eventEnum);

		/**
		* @brief Sets the border thickness of this button component.
		* @param[in] thickness - The new border thickness of the component.
		*/
		void SetBorderThickness(int thickness);

		/**
		* @brief Attaches the given function as a callback which is called when the button component is clicked.
		* @param[in] callbackFunc - The function to be attached as the callback.
		*/
		void SetClickCallback(std::function<void()> callbackFunc);

		/**
		* @brief Updates the logic of the button component.
		*/
		virtual void Update(float deltaTime) override = 0;

		/**
		* @brief Renders the button component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		virtual void Render(const Viewport& viewport) const override = 0;

		/**
		* @brief Returns the current position of the button component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the size of this button component.
		* @return The size of this component.
		*/
		const glm::ivec2& GetSize() const;

		/**
		* @brief Returns the button color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The button color attached to the specified event.
		*/
		const glm::vec4& GetColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the button border color which is displayed when the specified component event occurs.
		* @param[in] eventEnum - The component event to retrieve the attached color from.
		* The accepted enum values are: NO_EVENT, HOVERED_EVENT, and CLICKED_EVENT.
		*
		* @return The button border color attached to the specified event.
		*/
		const glm::vec4& GetBorderColor(ComponentEvent eventEnum) const;

		/**
		* @brief Returns the thickness of the button component's border.
		* @return The border thickness of the button.
		*/
		const int& GetBorderThickness() const;
	protected:
		/**
		* @brief Initialises the button component.
		*/
		virtual void InitializeComponent() override;

		/**
		* @brief Checks if the cursor is hovering on the button.
		* @return TRUE if cursor is hovering on button, FALSE otherwise.
		*/
		virtual bool IsCursorHovering() const;
	protected:
		glm::ivec2 m_position, m_size;
		glm::vec4 m_baseColor, m_hoverColor, m_clickedColor, m_currentColor;
		glm::vec4 m_baseBorderColor, m_hoverBorderColor, m_clickedBorderColor, m_currentBorderColor;
		int m_borderThickness;

		std::function<void()> m_onClickCallbackFunc;
	};
}

#endif
