#include <graphics/vertex_array.h>

namespace GUILib
{
	VertexArray::VertexArray() { glGenVertexArrays(1, &m_id); }

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

	void VertexArray::PushLayout(uint32_t index, uint32_t size, uint32_t stride, uint32_t offset, uint32_t divisor, bool normalized)
	{
		m_layouts.push_back({ index, size, GL_FLOAT, stride, offset, divisor, normalized });
	}

    void VertexArray::AttachBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer* indexBuffer)
    {
        // Bind the vertex array, then bind the vertex buffer (and index buffer if given one)
        glBindVertexArray(m_id);

        vertexBuffer.Bind();
        if (indexBuffer)
            indexBuffer->Bind();

        // Configure the vertex attribute pointers using the stored vertex layouts
        for (const VertexLayout& layout : m_layouts)
        {
            glEnableVertexAttribArray(layout.index);
            glVertexAttribPointer(layout.index, layout.size, layout.type, layout.normalized, layout.stride,
                (void*)((uint64_t)layout.offset));
            glVertexAttribDivisor(layout.index, layout.divisor);
        }

        m_layouts.clear();

        // Finally unbind all objects
        glBindVertexArray(0);

        vertexBuffer.Unbind();
        if (indexBuffer)
            indexBuffer->Unbind();
    }

    void VertexArray::Bind() const { glBindVertexArray(m_id); }

    void VertexArray::Unbind() const { glBindVertexArray(0); }

    const uint32_t& VertexArray::GetID() const { return m_id; }
}