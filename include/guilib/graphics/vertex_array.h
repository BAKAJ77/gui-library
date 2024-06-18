#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <graphics/buffer_objects.h>
#include <vector>

namespace GUILib
{
	/**
	* @brief This is a class for handing OpenGL vertex array operations.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC VertexArray
	{
	public:
		/**
		* @brief This is the default class constructor method.
		*/
		VertexArray();

		~VertexArray();

		/**
		* @brief Pushes a new vertex layout to the stack.
		* This specifies how an attribute of the vertex data is laid out in the vertex buffer passed in the next AttachBuffers() call. 
		* 
		* @param[in] index - The index of the vertex attribute.
		* @param[in] size - The number of components the vertex attribute has.
		* @param[in] stride - The offset (in bytes) between consecutive vertex attributes.
		* @param[in] offset - The offset (in bytes) of the first vertex attribute in the vertex buffer.
		* @param[in] divisor - Number of instances that will pass per update of the vertex attribute.
		* @param[in] normalized - Specifies whether fixed-point values should be normalized or converted directly as fixed-point values.
		* 
		* @remark Refer to glVertexAttribPointer and glVertexAttribDivisor khronos docs for more info.
		*/
		void PushLayout(uint32_t index, uint32_t size, uint32_t stride, uint32_t offset = 0, uint32_t divisor = 0, bool normalized = false);

		/**
		* @brief Attaches the vertex and index buffer to the vertex array.
		* 
		* @param[in] vertexBuffer - The vertex buffer to be attached.
		* @param[in] indexBuffer - The index buffer to be attached (Note that you can also pass nullptr if needed).
		*/
		void AttachBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer* indexBuffer = nullptr);

		/**
		* @brief Binds the vertex array.
		*/
		void Bind() const;

		/**
		* @brief Unbinds the vertex array.
		*/
		void Unbind() const;

		/**
		* @brief Returns the ID of the vertex array.
		* @return An unsigned int representing the ID of the vertex array.
		*/
		const uint32_t& GetID() const;
	private:
		struct VertexLayout
		{
			uint32_t index, size, type, stride, offset, divisor;
			bool normalized;
		};
	private:
		uint32_t m_id;
		std::vector<VertexLayout> m_layouts;
	};
}

#endif
