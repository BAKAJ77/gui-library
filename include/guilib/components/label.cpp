#include <components/label.h>
#include <external/glm/glm/gtc/matrix_transform.hpp>

namespace GUILib
{
	Label::Label(std::string_view text, glm::vec4 color, const Font* font, float fontSize) :
		m_font(font), m_text(text), m_position({ 0, 0 }), m_textColor(color), m_fontSize(fontSize), m_shouldUpdate(UpdateFlags::NONE),
		m_textLengthChanged(true)
	{
		this->InitializeComponent();
		this->GenerateTextGeometry();
		m_size = this->CalculateTextSize();
	}

	void Label::InitializeComponent() { m_shaders = ResourceLoader::GetInstance().GetShaders("Text"); }

	void Label::GenerateTextGeometry()
	{
		if (m_font && m_fontSize > 0 && !m_text.empty())
		{
			// If the text length remains the same, we can just reuse the allocated vertex buffer
			// However, if the length of the text has changed, then we have to delete and reallocate a new vertex buffer
			if (m_textLengthChanged)
			{
				if (m_geometry.vbo) // Delete the vertex buffer (if existing)
					delete m_geometry.vbo;

				// Allocate new vertex buffer
				m_geometry.vbo = new VertexBuffer(nullptr, m_text.size() * sizeof(float) * 24, GL_DYNAMIC_DRAW);

				// Create new vertex array (if not existing already), then setup vertex attributes and attach vertex buffer 
				if (!m_geometry.vao)
					m_geometry.vao = new VertexArray();

				m_geometry.vao->PushLayout(0, 2, 4 * sizeof(float));
				m_geometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
				m_geometry.vao->AttachBuffers(*m_geometry.vbo);

				m_textLengthChanged = false;
			}

			glm::vec2 cursorPos = glm::vec2(0.0f);
			for (size_t i = 0; i < m_text.size(); i++)
			{
				const Font::GlyphMetrics& glyph = m_font->GetGlyph(m_text[i]); // Get the glyph metrics for the character
				const glm::vec2 atlasSize = { (float)m_font->GetTextureAtlas()->GetWidth(), (float)m_font->GetTextureAtlas()->GetHeight() };

				// Calculate the position and size of the glyph
				int bearingX = i > 0 ? glyph.bearing.x : 0; // Don't add horizontal bearing on first glyph position

				const float scale = m_fontSize / 64.0f;
				const glm::vec2 glyphPos = { cursorPos.x + bearingX * scale, cursorPos.y + (glyph.size.y - glyph.bearing.y) * scale };
				const glm::vec2 glyphSize = { glyph.size.x * scale, glyph.size.y * scale };

				// Generate the vertex data
				float glyphVertexData[24] =
				{
					glyphPos.x, glyphPos.y, glyph.atlasOffsetX / atlasSize.x, glyph.size.y / atlasSize.y,
					glyphPos.x + glyphSize.x, glyphPos.y, (glyph.atlasOffsetX + glyph.size.x) / atlasSize.x, glyph.size.y / atlasSize.y,
					glyphPos.x + glyphSize.x, glyphPos.y - glyphSize.y, (glyph.atlasOffsetX + glyph.size.x) / atlasSize.x, 0.0f,

					glyphPos.x, glyphPos.y, glyph.atlasOffsetX / atlasSize.x, glyph.size.y / atlasSize.y,
					glyphPos.x, glyphPos.y - glyphSize.y, glyph.atlasOffsetX / atlasSize.x, 0.0f,
					glyphPos.x + glyphSize.x, glyphPos.y - glyphSize.y, (glyph.atlasOffsetX + glyph.size.x) / atlasSize.x, 0.0f
				};

				// Apply glyph advance amount onto the cursor's x position
				if (i > 0)
					cursorPos.x += glyph.advance.x * scale;
				else
					cursorPos.x += (glyph.advance.x - glyph.bearing.x) * scale;

				// Insert the generated vertex data into the buffer
				m_geometry.vbo->Update(glyphVertexData, sizeof(glyphVertexData), sizeof(float) * 24 * i);
			}
		}
	}

	glm::ivec2 Label::CalculateTextSize() const
	{
		glm::ivec2 textSize = { 0, 0 };

		if (m_font && m_fontSize > 0 && !m_text.empty())
		{
			int highestGlyphEdge = 0, lowestGlyphEdge = 0;

			for (size_t i = 0; i < m_text.size(); i++)
			{
				const Font::GlyphMetrics& glyph = m_font->GetGlyph(m_text[i]); // Get the glyph metrics for the character
				const float scale = m_fontSize / 64.0f;

				// Accumulate the glyph's horizontal metrics onto the horizontal text size counter
				if (i != m_text.size() - 1)
					textSize.x += glyph.advance.x * scale;
				else
					textSize.x += (glyph.bearing.x * scale) + (glyph.size.x * scale);

				// Check if the glyph is positioned higher or lower than the rest
				const int glyphBottom = (glyph.size.y - glyph.bearing.y) * scale,
					glyphTop = glyph.bearing.y * scale;

				if (glyphTop > highestGlyphEdge)
					highestGlyphEdge = glyphTop;
				if (glyphBottom < lowestGlyphEdge)
					lowestGlyphEdge = glyphBottom;
			}

			textSize.y = highestGlyphEdge + lowestGlyphEdge; // Calculate the text string height from retrieved highest and lowest glyph edges
		}

		return textSize;
	}

	void Label::SetPosition(glm::ivec2 pos) { m_position = pos; }

	void Label::SetFont(const Font* font)
	{
		if (m_font != font)
		{
			m_font = font;
			m_shouldUpdate = UpdateFlags::UPDATE_ALL;
		}
	}

	void Label::SetFontSize(float size)
	{
		if (m_fontSize != size)
		{
			m_fontSize = size;
			m_shouldUpdate = UpdateFlags::UPDATE_ALL;
		}
	}

	void Label::SetText(std::string_view text)
	{
		if (m_text != text)
		{
			if (m_text.size() != text.size())
				m_textLengthChanged = true;

			m_text = text;
			m_shouldUpdate = UpdateFlags::UPDATE_ALL;
		}
	}

	void Label::SetTextColor(glm::vec4 color) { m_textColor = color; }

	void Label::Update(float deltaTime)
	{
		if (m_shouldUpdate == UpdateFlags::UPDATE_ALL || m_shouldUpdate == UpdateFlags::UPDATE_GEOMETRY_DATA)
			this->GenerateTextGeometry();
		else if (m_shouldUpdate == UpdateFlags::UPDATE_ALL || m_shouldUpdate == UpdateFlags::UPDATE_TEXT_SIZE_DATA)
			m_size = this->CalculateTextSize();
		
		m_shouldUpdate = UpdateFlags::NONE;
	}

	void Label::Render(const Viewport& viewport) const
	{
		if (m_font && !m_text.empty())
		{
			// Construct the model matrix
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, { m_position, 0.0f });
			
			// Bind the shader and setup the shader uniforms
			m_shaders->Bind();
			m_shaders->SetUniform("fontAtlasSampler", 0);
			m_shaders->SetUniformGLM("model", modelMatrix);
			m_shaders->SetUniformGLM("viewport", viewport.GetMatrix());
			m_shaders->SetUniformGLM("textColor", m_textColor);

			// Render the image component
			m_geometry.vao->Bind();
			m_font->GetTextureAtlas()->Bind(0);

			glDrawArrays(GL_TRIANGLES, 0, m_text.size() * 6);
		}
	}

	const glm::ivec2& Label::GetPosition() const { return m_position; }

	const Font* Label::GetFont() const { return m_font; }

	const float Label::GetFontSize() const { return m_fontSize; }

	const std::string& Label::GetText() const { return m_text; }

	const glm::vec4& Label::GetTextColor() const { return m_textColor; }

	const glm::ivec2& Label::GetSize() const 
	{ 
		// Update the text size data before returning if requested
		if (m_shouldUpdate == UpdateFlags::UPDATE_ALL || m_shouldUpdate == UpdateFlags::UPDATE_TEXT_SIZE_DATA)
		{
			m_size = this->CalculateTextSize();
			m_shouldUpdate = m_shouldUpdate == UpdateFlags::UPDATE_ALL ? UpdateFlags::UPDATE_GEOMETRY_DATA : UpdateFlags::NONE;
		}

		return m_size; 
	}
}