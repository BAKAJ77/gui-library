#include <graphics/buffer_objects.h>

namespace GUILib
{
    VertexBuffer::VertexBuffer(const void* data, uint32_t size, uint32_t usage)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer() 
    { 
        if (m_id > 0)
            glDeleteBuffers(1, &m_id);
    }

    void VertexBuffer::Update(const void* data, uint32_t size, uint32_t offset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

    void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    const uint32_t& VertexBuffer::GetID() const { return m_id; }

    IndexBuffer::IndexBuffer(const void* data, uint32_t size, uint32_t usage)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IndexBuffer::~IndexBuffer() 
    { 
        if (m_id > 0)
            glDeleteBuffers(1, &m_id);
    }

    void IndexBuffer::Update(const void* data, uint32_t size, uint32_t offset)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

    void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    const uint32_t& IndexBuffer::GetID() const { return m_id; }

    TextureBuffer2D::TextureBuffer2D(int internalFormat, uint32_t width, uint32_t height, uint32_t format, uint32_t type,
        const void* pixelData, bool genMipmaps) :
        m_width(width), m_height(height)
    {
        // Generate and bind the texture buffer then configure wrap and filter modes
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        this->SetDefaultModeSettings();

        // Fill the texture buffer with the pixel data given (then generate mipmaps if specified to do so)
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, pixelData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind the texture buffer
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    TextureBuffer2D::~TextureBuffer2D() 
    { 
        if (m_id > 0)
            glDeleteTextures(1, &m_id);
    }

    void TextureBuffer2D::SetDefaultModeSettings() const
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void TextureBuffer2D::SetWrapMode(uint32_t sAxis, uint32_t tAxis)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sAxis);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tAxis);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer2D::SetFilterMode(uint32_t min, uint32_t mag)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer2D::Update(int offsetX, int offsetY, uint32_t width, uint32_t height, uint32_t format, uint32_t type,
        const void* pixelData)
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, format, type, pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer2D::Bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }

    void TextureBuffer2D::Bind(uint32_t textureUnit) const
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void TextureBuffer2D::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    const uint32_t& TextureBuffer2D::GetID() const { return m_id; }

    const uint32_t& TextureBuffer2D::GetWidth() const { return m_width; }

    const uint32_t& TextureBuffer2D::GetHeight() const { return m_height; }
}