#ifndef IMAGE_H
#define IMAGE_H

#include <components/component.h>
#include <external/glm/glm/glm.hpp>
#include <string>

namespace GUILib
{
	class TextureBuffer2D;
	
	/**
	* @brief This is a component class for displaying images.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack. 
	*/
	class LIB_DECLSPEC Image : public Component
	{
	public:
		/**
		* @brief This is a class constructor that assigns the given texture to this image component.
		* @param[in] texture - The texture buffer that will be assigned to the image component.
		*/
		Image(const TextureBuffer2D* texture);

		~Image() = default;

		/**
		* @brief Sets the current position of the image component.
		* @param[in] pos - The new position of the component.
		*/
		void SetPosition(glm::ivec2 pos);

		/**
		* @brief Sets the current size of the image component.
		* @param[in] pos - The new size of the component.
		*/
		void SetSize(glm::ivec2 size);

		/**
		* @brief Assigns the given texture to this image component.
		* @param[in] texture - The texture buffer that will be assigned to the image component.
		*/
		void SetTexture(const TextureBuffer2D* texture);

		/**
		* @brief Updates the logic of the image component.
		* This does nothing since this is a static component.
		* 
		* @param[in] deltaTime - The elapsed time between the previous and current frame.
		*/
		void Update(float deltaTime) override;

		/**
		* @brief Renders the image component.
		* @param[in] viewport - The viewport where the component is being rendered to.
		*/
		void Render(const Viewport& viewport) const override;

		/**
		* @brief Returns the current position of the image component.
		* @return The position of the component.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the current size of the image component.
		* @return The size of the component.
		*/
		const glm::ivec2& GetSize() const;
		
		/**
		* @brief Returns the texture assigned to this image component.
		* @return The texture buffer assigned to this component.
		*/
		const TextureBuffer2D* GetTextureBuffer() const;
	private:
		/**
		* @brief Initialises the image component.
		*/
		void InitializeComponent() override;
	private:
		glm::ivec2 m_position, m_size;
		const TextureBuffer2D* m_textureBuffer;
	};
}

#endif