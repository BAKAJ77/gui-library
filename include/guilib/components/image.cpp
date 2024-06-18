#include <components/image.h>
#include <utilities/resource_loader.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	Image::Image(const TextureBuffer2D* texture) :
		m_textureBuffer(texture), m_position({ 0, 0 })
	{
		this->InitializeComponent();
		if (texture)
			m_size = { (int)m_textureBuffer->GetWidth(), (int)m_textureBuffer->GetHeight() };
	}

	void Image::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void Image::SetSize(glm::ivec2 size) { m_size = size; }

	void Image::InitializeComponent()
	{
		m_shaders = ResourceLoader::GetInstance().GetShaders("Geometry");
		m_geometry = *ResourceLoader::GetInstance().GetGeometry("Square");
	}

	void Image::SetTexture(const TextureBuffer2D* texture) 
	{ 
		m_textureBuffer = texture; 
		if (texture)
			m_size = { (int)m_textureBuffer->GetWidth(), (int)m_textureBuffer->GetHeight() };
	}

	void Image::Update(float deltaTime) {}

	void Image::Render(const Viewport& viewport) const
	{
		if (m_textureBuffer)
		{
			// Construct the model matrix
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
			modelMatrix = glm::scale(modelMatrix, { m_size, 0.0f });

			// Bind the shader and setup the shader uniforms
			m_shaders->Bind();
			m_shaders->SetUniform("textureSampler", 0);
			m_shaders->SetUniform("useTextures", true);
			m_shaders->SetUniformGLM("model", modelMatrix);
			m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());

			// Render the image component
			m_geometry.vao->Bind();
			m_textureBuffer->Bind(0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	const glm::ivec2& Image::GetPosition() const { return m_position; }

	const glm::ivec2& Image::GetSize() const { return m_size; }

	const TextureBuffer2D* Image::GetTextureBuffer() const { return m_textureBuffer; }
}