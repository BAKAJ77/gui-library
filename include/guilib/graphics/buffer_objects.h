#ifndef BUFFER_OBJECTS_H
#define BUFFER_OBJECTS_H

#include <utilities/libexport.h>
#include <external/glad/glad.h>
#include <stdint.h>

namespace GUILib
{
	/**
	* @brief This is a class for handing OpenGL vertex buffer operations.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC VertexBuffer
	{
	public:
		/**
		* @brief This is a class constructor method for creating and setting up the OpenGL vertex buffer object.
		* 
		* @param[in] data - The data to be stored in the vertex buffer.
		* @param[in] size - The size of the data.
		* @param[in] usage - Enum indicating the expected usage pattern of the vertex buffer.
		* 
		* @remark See glBufferData khronos docs for info on accepted enum vales for usage parameter.
		*/
		VertexBuffer(const void* data, uint32_t size, uint32_t usage);

		~VertexBuffer();

		/**
		* @brief Updates the vertex buffer with the new data given.
		* 
		* @param[in] data - The new data to be written into the vertex buffer.
		* @param[in] size - The size of the data.
		* @param[in] offset - The offset position, in the vertex buffer, to write the new data to.
		*/
		void Update(const void* data, uint32_t size, uint32_t offset);

		/**
		* @brief Binds the vertex buffer.
		*/
		void Bind() const;

		/**
		* @brief Unbinds the vertex buffer.
		*/
		void Unbind() const;

		/**
		* @brief Returns the ID of the vertex buffer.
		* @return An unsigned int representing the ID of the vertex buffer.
		*/
		const uint32_t& GetID() const;
	private:
		uint32_t m_id;
	};

	/**
	* @brief This is a class for handing OpenGL index buffer operations.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC IndexBuffer
	{
	public:
		/**
		* @brief This is a class constructor method for creating and setting up the OpenGL index buffer object.
		*
		* @param[in] data - The data to be stored in the index buffer.
		* @param[in] size - The size of the data.
		* @param[in] usage - Enum indicating the expected usage pattern of the index buffer.
		* 
		* @remark See glBufferData khronos docs for info on accepted enum vales for usage parameter.
		*/
		IndexBuffer(const void* data, uint32_t size, uint32_t usage);

		~IndexBuffer();

		/**
		* @brief Updates the index buffer with the new data given.
		*
		* @param[in] data - The new data to be written into the index buffer.
		* @param[in] size - The size of the data.
		* @param[in] offset - The offset position, in the index buffer, to write the new data to.
		*/
		void Update(const void* data, uint32_t size, uint32_t offset);

		/**
		* @brief Binds the index buffer.
		*/
		void Bind() const;

		/**
		* @brief Unbinds the index buffer.
		*/
		void Unbind() const;

		/**
		* @brief Returns the ID of the index buffer.
		* @return An unsigned int representing the ID of the index buffer.
		*/
		const uint32_t& GetID() const;
	private:
		uint32_t m_id;
	};

	/**
	* @brief This is a class for handing OpenGL 2-dimensional texture buffer operations.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC TextureBuffer2D
	{
	public:
		/**
		* @brief This is a class constructor method for creating and setting up the OpenGL texture buffer object.
		* 
		* @param[in] internalFormat - Enum specifying the number of colour components in the texture.
		* @param[in] width - The width of the texture.
		* @param[in] height - The height of the texture.
		* @param[in] format - Enum specifying the format of the pixel data.
		* @param[in] type - Enum specifying the data type of the pixel data.
		* @param[in] pixelData - The pixel data to be stored in the texture buffer.
		* @param[in] genMipmaps - Specifies whether or not to generate texture mipmaps.
		* 
		* @remark See glTexImage2d khronos docs for info on accepted enum vales for internalFormat, format, and type parameters.
		*/
		TextureBuffer2D(int internalFormat, uint32_t width, uint32_t height, uint32_t format, uint32_t type,
			const void* pixelData, bool genMipmaps);

		~TextureBuffer2D();

		/**
		* @brief Sets the wrapping mode used for the texture buffer.
		* 
		* @param[in] sAxis - Enum specifying the wrapping mode to use along the S axis of the texture.
		* @param[in] tAxis - Enum specifying the wrapping mode to use along the T axis of the texture.
		* 
		* @remark See glTexParameter khronos docs for info on accepted enum vales for both parameters.
		*/
		void SetWrapMode(uint32_t sAxis, uint32_t tAxis);

		/**
		* @brief Sets the filtering mode used for the texture buffer.
		* 
		* @param[in] min - Enum specifying the filtering mode to use when the texture is minified.
		* @param[in] mag - Enum specifying the filtering mode to use when the texture is magnified.
		* 
		* @remark See glTexParameter khronos docs for info on accepted enum vales for both parameters.
		*/
		void SetFilterMode(uint32_t min, uint32_t mag);

		/**
		* @brief Updates the texture buffer with the new pixel data given.
		* 
		* @param[in] offsetX - The offset position, along the X axis of the texture buffer, that the new pixel data should be written to.
		* @param[in] offsetY - The offset position, along the Y axis of the texture buffer, that the new pixel data should be written to.
		* @param[in] width - The width of the new texture pixel data.
		* @param[in] height - The height of the new texture pixel data.
		* @param[in] format - Enum specifying the format of the pixel data.
		* @param[in] type - Enum specifying the data type of the pixel data.
		* @param[in] pixelData - The new pixel data to be written into the texture buffer.
		* 
		* @remark See glTexSubImage2d khronos docs for info on accepted enum vales for format and type parameters.
		*/
		void Update(int offsetX, int offsetY, uint32_t width, uint32_t height, uint32_t format, uint32_t type,
			const void* pixelData);

		/**
		* @brief Binds the texture buffer.
		*/
		void Bind() const;

		/**
		* @brief Binds the texture buffer.
		* @param[in] textureIndex - Enum specifying the texture unit to make active.
		* 
		* @remark See glActiveTexture khronos docs for info on accepted enum vales for the textureUnit parameter.
		*/
		void Bind(uint32_t textureUnit) const;

		/**
		* @brief Unbinds the texture buffer.
		*/
		void Unbind() const;

		/**
		* @brief Returns the ID of the texture buffer.
		* @return An unsigned integer representing the ID of the texture buffer.
		*/
		const uint32_t& GetID() const;

		/**
		* @brief Returns the width of the texture buffer.
		* @return An unsigned integer representing the width of the texture buffer.
		*/
		const uint32_t& GetWidth() const;

		/**
		* @brief Returns the height of the texture buffer.
		* @return An unsigned integer representing the height of the texture buffer.
		*/
		const uint32_t& GetHeight() const;
	private:
		/**
		* @brief Configures default wrapping and filtering modes for the texture buffer.
		*/
		void SetDefaultModeSettings() const;
	private:
		uint32_t m_id, m_width, m_height;
	};
}

#endif