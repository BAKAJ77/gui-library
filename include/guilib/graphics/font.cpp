#include <graphics/font.h>
#include <graphics/buffer_objects.h>
#include <algorithm>

namespace GUILib
{
	Font::Font(TextureBuffer2D* textureAtlas, const std::unordered_map<char, GlyphMetrics>& glyphMetricsSet) :
		m_textureAtlas(textureAtlas), m_glyphMetricsSet(glyphMetricsSet)
	{}

	Font::~Font() { delete m_textureAtlas; }

	const Font::GlyphMetrics& Font::GetGlyph(char asciiCode) const { return m_glyphMetricsSet.find(asciiCode)->second; }

	const std::unordered_map<char, Font::GlyphMetrics>& Font::GetGlyphSet() const { return m_glyphMetricsSet; }

	TextureBuffer2D* Font::GetTextureAtlas() { return m_textureAtlas; }

	const TextureBuffer2D* Font::GetTextureAtlas() const { return m_textureAtlas; }
}