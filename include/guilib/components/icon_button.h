#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <components/button.h>

namespace GUILib
{
	class TextureBuffer2D;

	/**
	* @brief This is a component class for handling and displaying icon buttons.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC IconButton : public Button
	{
	public:
		/**
		* @brief This is a class constructor that assigns the given texture to this icon button component.
		* @param[in] texture - The texture buffer that will be assigned to the icon button component.
		*/
		IconButton(const TextureBuffer2D* texture);

		~IconButton() = default;

		/**
		* @brief Updates the logic of the icon button component.
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the icon button component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;
	private:
		/**
		* @brief Initialises the icon button component.
		*/
		void InitializeComponent() override;
	private:
		const TextureBuffer2D* m_iconTexture;
		bool m_isButtonHeld;
	};
}

#endif
