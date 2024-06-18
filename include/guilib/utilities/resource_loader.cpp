#include <utilities/resource_loader.h>

#include <external/stb/stb_image.h>
#include <external/freetype/include/ft2build.h>
#include <external/freetype/include/freetype/freetype.h>
#include <external/freetype/include/freetype/ftmm.h>

#include <fstream>
#include <sstream>

namespace GUILib
{
	ResourceLoader::ResourceLoader() :
		m_freetypeLib(nullptr)
	{
		// Initialize the FreeType library
		this->CheckFTFunctionResult(FT_Init_FreeType(&m_freetypeLib));
	}

	void ResourceLoader::FreeResources()
	{
		// Clean up FreeType library
		this->CheckFTFunctionResult(FT_Done_FreeType(m_freetypeLib));

		// Free all shader resources
		for (auto& shader : m_loadedShaders)
		{
			if (shader.second)
				delete shader.second;
		}

		// Free all texture resources
		for (auto& texture : m_loadedTextures)
		{
			if (texture.second)
				delete texture.second;
		}

		// Free all font resources
		for (auto& font : m_loadedFonts)
		{
			if (font.second)
				delete font.second;
		}

		// Free all geometry resources
		for (auto& geometry : m_storedGeometry)
		{
			delete geometry.second.vbo;
			delete geometry.second.vao;

			if (geometry.second.ibo)
				delete geometry.second.ibo;
		}
	}

	void ResourceLoader::CheckFTFunctionResult(FT_Error resultCode) const
	{
		if (resultCode > 0)
			throw std::exception(FT_Error_String(resultCode));
	}

	void ResourceLoader::LoadShadersFromFile(std::string_view id, std::string_view vshFilePath, std::string_view fshFilePath,
		std::string_view gshFilePath)
	{
		// Make sure a shader with the specified ID doesn't exist already
		if (m_loadedShaders.find(id.data()) != m_loadedShaders.end())
			return;

		// Load the shader code from the shader files
		std::ifstream vertexFileStream, fragmentFileStream, geometryFileStream;

		vertexFileStream.open(vshFilePath.data());
		if (vertexFileStream.fail())
			throw std::exception((std::string("Failed to open the vertex shader file at path: ") + vshFilePath.data()).c_str());
			
		fragmentFileStream.open(fshFilePath.data());
		if (fragmentFileStream.fail())
			throw std::exception((std::string("Failed to open the fragment shader file at path: ") + fshFilePath.data()).c_str());

		if (!gshFilePath.empty()) // If a geometry shader file path is specified, then open it too
		{
			geometryFileStream.open(gshFilePath.data());
			if (geometryFileStream.fail())
				throw std::exception((std::string("Failed to open the geometry shader file at path: ") + gshFilePath.data()).c_str());
		}

		std::stringstream vshContentsStream, fshContentsStream, gshContentsStream;
		vshContentsStream << vertexFileStream.rdbuf();
		fshContentsStream << fragmentFileStream.rdbuf();

		if (geometryFileStream.is_open()) // If a geometry shader file is opened, then load its contents
			gshContentsStream << geometryFileStream.rdbuf();

		std::string vshContentsStr, fshContentsStr, gshContentsStr;
		vshContentsStr = vshContentsStream.str();
		fshContentsStr = fshContentsStream.str();
		gshContentsStr = gshContentsStream.str();

		// Add the loaded shaders to the unordered map
		m_loadedShaders.insert({ id.data(), new ShaderProgram(vshContentsStr, fshContentsStr, gshContentsStr) });
	}

	void ResourceLoader::LoadShadersFromString(std::string_view id, std::string_view vshSourceCode, std::string_view fshSourceCode, 
		std::string_view gshSourceCode)
	{
		// Make sure a shader with the specified ID doesn't exist already
		if (m_loadedShaders.find(id.data()) != m_loadedShaders.end())
			return;

		// Add the loaded shaders to the unordered map
		m_loadedShaders.insert({ id.data(), new ShaderProgram(vshSourceCode, fshSourceCode, gshSourceCode) });
	}

	void ResourceLoader::LoadTextureFromFile(std::string_view id, std::string_view filePath, bool flipImageOnLoad)
	{
		// Make sure a texture with the specified ID doesn't exist already
		if (m_loadedTextures.find(id.data()) != m_loadedTextures.end())
			return;

		// Add the loaded texture image to the unordered map
		m_loadedTextures.insert({ id.data(), this->LoadTextureFromFile(filePath, flipImageOnLoad) });
	}

	TextureBuffer2D* ResourceLoader::LoadTextureFromFile(std::string_view filePath, bool flipImageOnLoad)
	{
		// Load the pixel data of the texture from the specified file
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		int imageWidth = 0, imageHeight = 0, imageChannels = 0;
		uint8_t* imagePixelData = stbi_load(filePath.data(), &imageWidth, &imageHeight, &imageChannels, 0);
		if (!imagePixelData)
			throw std::exception((stbi_failure_reason() + std::string(" ") + std::string(filePath)).c_str());

		uint32_t formatEnum = imageChannels > 3 ? GL_RGBA : GL_RGB;
		TextureBuffer2D* buffer = new TextureBuffer2D(formatEnum, (uint32_t)imageWidth, (uint32_t)imageHeight, formatEnum, GL_UNSIGNED_BYTE,
			imagePixelData, true);

		stbi_image_free(imagePixelData);
		return buffer;
	}

	void ResourceLoader::LoadFontFromFile(std::string_view id, std::string_view filepath)
	{
		// Make sure a font with the specified ID doesn't exist already
		if (m_loadedFonts.find(id.data()) != m_loadedFonts.end())
			return;

		// Load the font face from file, throw exception if font face loading operation failed
		FT_Face fontFace = nullptr;
		this->CheckFTFunctionResult(FT_New_Face(m_freetypeLib, filepath.data(), 0, &fontFace));
		this->CheckFTFunctionResult(FT_Set_Pixel_Sizes(fontFace, 0, 64));

		// Firstly load the glyph metrics of each ascii character
		// These metrics will also be used to calculate how much memory to allocate for the texture buffer 
		uint32_t textureAtlasWidth = 0, textureAtlasHeight = 0;
		std::unordered_map<char, Font::GlyphMetrics> glyphMetricsSet;

		for (char asciiCode = 32; asciiCode < 127; asciiCode++)
		{
			this->CheckFTFunctionResult(FT_Load_Char(fontFace, asciiCode, FT_LOAD_BITMAP_METRICS_ONLY));

			// Store the glyph metrics of the ascii character
			Font::GlyphMetrics metrics;
			metrics.bearing = { fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top };
			metrics.size = { fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows };
			metrics.advance = { (fontFace->glyph->advance.x >> 6), (fontFace->glyph->advance.y >> 6) };
			metrics.atlasOffsetX = textureAtlasWidth;

			glyphMetricsSet[asciiCode] = metrics;

			// Update the texture atlas width and height counter variables
			constexpr uint32_t glyphAtlasSpacing = 10;
			textureAtlasWidth += ((uint32_t)metrics.size.x + glyphAtlasSpacing);
			if (textureAtlasHeight < (uint32_t)metrics.size.y)
				textureAtlasHeight = (uint32_t)metrics.size.y;
		}

		// Initialize the texture atlas buffer
		TextureBuffer2D* textureAtlas = new TextureBuffer2D(GL_RED, textureAtlasWidth, textureAtlasHeight, GL_RED, GL_UNSIGNED_BYTE, 
			nullptr, false);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disregard unpack byte-alignment

		// Generate bitmap for each glyph, and insert the bitmap pixel data into the texture buffer
		textureAtlas->Bind();
		for (char asciiCode = 32; asciiCode < 127; asciiCode++)
		{
			this->CheckFTFunctionResult(FT_Load_Char(fontFace, asciiCode, FT_LOAD_RENDER));
			const Font::GlyphMetrics& metrics = glyphMetricsSet[asciiCode];
			textureAtlas->Update(metrics.atlasOffsetX, 0, (uint32_t)metrics.size.x, (uint32_t)metrics.size.y, GL_RED,
				GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);
		}

		textureAtlas->SetWrapMode(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
		FT_Done_Face(fontFace); // Free the allocated freetype face 

		// Add the loaded font to the unordered map
		m_loadedFonts.insert({ id.data(), new Font(textureAtlas, glyphMetricsSet) });
	}

	void ResourceLoader::AddGeometry(std::string_view id, Geometry& geometry)
	{
		// Make sure the geometry with the specified ID doesn't exist already
		if (m_storedGeometry.find(id.data()) != m_storedGeometry.end())
			return;

		// Add the given geometry to the unordered map
		m_storedGeometry.insert({ id.data(), geometry });
	}

	ShaderProgram* ResourceLoader::GetShaders(std::string_view id)
	{
		// Lookup the shaders based on the ID given
		auto iterator = m_loadedShaders.find(id.data());
		if (iterator != m_loadedShaders.end())
			return iterator->second;

		return nullptr; // No shaders matching the ID given was found
	}

	TextureBuffer2D* ResourceLoader::GetTexture(std::string_view id)
	{
		// Lookup the texture based on the ID given
		auto iterator = m_loadedTextures.find(id.data());
		if (iterator != m_loadedTextures.end())
			return iterator->second;

		return nullptr; // No texture matching the ID given was found
	}

	Font* ResourceLoader::GetFont(std::string_view id)
	{
		// Lookup the font based on the ID given
		auto iterator = m_loadedFonts.find(id.data());
		if (iterator != m_loadedFonts.end())
			return iterator->second;

		return nullptr; // No font matching the ID given was found
	}

	ResourceLoader::Geometry* ResourceLoader::GetGeometry(std::string_view id)
	{
		// Lookup the geometry based on the ID given
		auto iterator = m_storedGeometry.find(id.data());
		if (iterator != m_storedGeometry.end())
			return &iterator->second;

		return nullptr; // No geometry matching the ID given was found
	}

	ResourceLoader& ResourceLoader::GetInstance()
	{
		static ResourceLoader instance;
		return instance;
	}
}