#ifndef FREETYPE_FONT_H
#define FREETYPE_FONT_H

#include <utilities/libexport.h>
#include <external/glm/glm/glm.hpp>
#include <unordered_map>

namespace GUILib
{
	class TextureBuffer2D;

	/**
	* @brief This class stores the font data necessary in order to render text using it.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC Font
	{
	public:
		/**
		* @brief A struct used for containing the metric data for a glyph.
		*/
		struct GlyphMetrics
		{
			glm::ivec2 size; // The size of the glyph
			glm::ivec2 bearing; // The bearing of the glyph
			glm::ivec2 advance; // The amount to increment the cursor position after rendering the glyph (must be measured in pixels).

			uint32_t atlasOffsetX; // The horizontal offset of the glyph bitmap in the font texture atlas
		};

		/**
		* @brief This is a class constructor that stores the given texture atlas and glyph metrics set for the font.
		* @param[in] textureAtlas - The texture atlas of the font, should contain all glyph bitmaps.
		* Note that this class will take ownership of the texture buffer pointer, therefore it will be automatically deleted it upon
		* destruction of the Font object.
		* 
		* @param[in] glyphMetricsSet - A set of metrics data for each glyph included in the font.
		*/
		Font(TextureBuffer2D* textureAtlas, const std::unordered_map<char, GlyphMetrics>& glyphMetricsSet);

		~Font();

		/**
		* @brief Returns the metrics data for the specified glyph.
		* @param[in] asciiCode - The ascii code for the glyph to be looked up.
		* @return The metrics data for the specified glyph.
		*/
		const GlyphMetrics& GetGlyph(char asciiCode) const;
		
		/**
		* @brief Returns set of metrics data for every glyph included in the font.
		* @return A set of metrics data for every available glyph in the font.
		*/
		const std::unordered_map<char, GlyphMetrics>& GetGlyphSet() const;

		/**
		* @brief Returns the texture buffer containing the bitmaps of every glyph in the font.
		* @return The font's texture atlas.
		*/
		TextureBuffer2D* GetTextureAtlas();

		/**
		* @brief Returns the texture buffer containing the bitmaps of every glyph in the font.
		* @return The font's texture atlas.
		*/
		const TextureBuffer2D* GetTextureAtlas() const;
	private:
		TextureBuffer2D* m_textureAtlas;
		std::unordered_map<char, GlyphMetrics> m_glyphMetricsSet;
	};
}

#endif