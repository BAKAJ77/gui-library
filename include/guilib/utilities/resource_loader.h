#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <graphics/shader_program.h>
#include <graphics/vertex_array.h>
#include <graphics/font.h>

typedef struct FT_LibraryRec_* FT_Library;
typedef int FT_Error;

namespace GUILib
{
	/**
	* @brief This is a class for loading and managing resources used by the graphical user interface.
	*/
	class LIB_DECLSPEC ResourceLoader
	{
	public:
		/**
		* @brief This a struct for containing OpenGL buffers that store geometry vertex and index data.
		*/
		struct Geometry
		{
			VertexBuffer* vbo = nullptr;
			IndexBuffer* ibo = nullptr;
			VertexArray* vao = nullptr;
		};

		~ResourceLoader() = default;

		/**
		* @brief Frees up allocated resources tracked by the resource manager.
		*/
		void FreeResources();

		/**
		* @brief Loads the shaders from the file paths specified, the resulting shader program is stored in the resource loader.
		* If an error occurs while loading the shaders, an exception will be thrown with error message information.
		* If a shader already exists with the given ID, then the given shaders will not be loaded and stored.
		* 
		* @param[in] id - The ID to be assigned to the newly loaded shaders.
		* @param[in] vshFilepath - The file path of the vertex shader.
		* @param[in] fshFilepath - The file path of the index shader.
		* @param[in] gshFilepath - The file path of the geometry shader (this is an optional parameter).
		*/
		void LoadShadersFromFile(std::string_view id, std::string_view vshFilepath, std::string_view fshFilepath, 
			std::string_view gshFilepath = std::string_view());

		/**
		* @brief Loads the shaders from the shader source code strings given, the resulting loaded texture will be stored by the resource loader.
		* If an error occurs while compiling or linking the shaders, an exception will be thrown with the fetched OpenGL error log message.
		* If a shader already exists with the given ID, then the given shaders will not be loaded and stored.
		*
		* @param[in] id - The ID to be assigned to the newly added shaders.
		* @param[in] vshCodeContents - A string containing the source code of the vertex shader.
		* @param[in] fshCodeContents - A string containing the source code of the fragment shader.
		* @param[in] gshCodeContents - A string containing the source code of the geometry shader (this is an optional parameter).
		*/
		void LoadShadersFromString(std::string_view id, std::string_view vshSourceCode, std::string_view fshSourceCode, 
			std::string_view gshSourceCode = std::string_view());

		/**
		* @brief Loads an image texture from the file path specified, the resulting loaded texture will be stored by the resource loader.
		* If an error occurs while loading the image texture, an exception will be thrown with an error log message.
		* If a texture already exists with the given ID, then the given texture will not be loaded and stored.
		* 
		* @param[in] id - The ID to be assigned to the newly added texture.
		* @param[in] filepath - The file path of the image file to be loaded.
		* @param[in] flipImageOnLoad - Specifies whether or not to flip the image on load.
		*/
		void LoadTextureFromFile(std::string_view id, std::string_view filepath, bool flipImageOnLoad);

		/**
		* @brief Loads an image texture from the file path specified, the resulting loaded texture will not be stored by the resource loader.
		* If an error occurs while loading the image texture, an exception will be thrown with an error log message.
		*
		* @param[in] filepath - The file path of the image file to be loaded.
		* @param[in] flipImageOnLoad - Specifies whether or not to flip the image on load.
		*/
		TextureBuffer2D* LoadTextureFromFile(std::string_view filepath, bool flipImageOnLoad);
	

		/**
		* @brief Loads the font stored at the file path specified, the resulting loaded font will be stored by the resource loader.
		* If an error occurs while loading the font, an exception will be thrown with an error log message.
		* If a loaded font already exists with the given ID, then the given font will not be loaded and stored.
		*
		* @param[in] id - The ID to be assigned to the newly added texture.
		* @param[in] filepath - The file path of the font file to be loaded.
		*/
		void LoadFontFromFile(std::string_view id, std::string_view filepath);

		/**
		* @brief The resource loader stores the geometry object given.
		* If a geometry object already exists with the given ID, then the given geometry will not be loaded and stored.
		* 
		* @param[in] id - The ID to be assigned to the newly added geometry.
		* @param[in] geometry - The geometry to be stored.
		*/
		void AddGeometry(std::string_view id, Geometry& geometry);

		/**
		* @brief Returns the shaders identified by the ID given.
		* 
		* @param[in] id - The ID of the shaders to be looked up.
		* @return A pointer to the shaders identified by the given ID, however if the shader specfied doesn't exist then nullptr is returned.
		*/
		ShaderProgram* GetShaders(std::string_view id);

		/**
		* @brief Returns the texture identified by the ID given.
		*
		* @param[in] id - The ID of the texture to be looked up.
		* @return A pointer to the texture identified by the given ID, however if the texture specfied doesn't exist then nullptr is returned.
		*/
		TextureBuffer2D* GetTexture(std::string_view id);

		/**
		* @brief Returns the font identified by the ID given.
		*
		* @param[in] id - The ID of the font to be looked up.
		* @return A pointer to the font identified by the given ID, however if the font specfied doesn't exist then nullptr is returned.
		*/
		Font* GetFont(std::string_view id);

		/**
		* @brief Returns the geometry identified by the ID given.
		*
		* @param[in] id - The ID of the geometry to be looked up.
		* @return A pointer to the geometry identified by the given ID, however if the geometry specfied doesn't exist then nullptr is returned.
		*/
		Geometry* GetGeometry(std::string_view id);

		/**
		* @brief Returns a singleton instance of this class.
		* @return Singleton instance object of this class.
		*/
		static ResourceLoader& GetInstance();
	private:
		/**
		* @brief This is the default class constructor.
		*/
		ResourceLoader();

		/**
		* @brief Utility method for checking whether or not an executed freetype function was successful.
		* An exception will be thrown if the freetype function failed.
		* @param[in] resultCode - The code returned from the freetype function.
		*/
		void CheckFTFunctionResult(FT_Error resultCode) const;
	private:
		std::unordered_map<std::string, ShaderProgram*> m_loadedShaders;
		std::unordered_map<std::string, TextureBuffer2D*> m_loadedTextures;
		std::unordered_map<std::string, Font*> m_loadedFonts;
		std::unordered_map<std::string, Geometry> m_storedGeometry;

		FT_Library m_freetypeLib;
	};

	namespace ResourceConstants
	{
		static constexpr float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		static constexpr uint32_t squareIndices[] = { 0, 1, 2, 0, 3, 2 };

		static constexpr float triangleVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.5f, 1.0f
		};

		static constexpr float lineVertices[] =
		{
			-0.5f, 0.0f, 0.0f, 0.5f,
			 0.5f, 0.0f, 1.0f, 0.5f
		};

		static constexpr float checkmarkVertices[] =
		{
			-0.5f,  0.0f,  0.0f, 0.5f,
			 0.0f,  0.5f,  0.5f, 0.0f,
			 0.0f,  0.56f, 0.5f, 0.0f,
			 0.5f, -0.5f,  1.0f, 1.0f
		};

		static constexpr float circleGeoemtryAngleStep = 2.0f;

		static constexpr char* geometryVshSrc =
		{
			"#version 330 core\n"
			"layout (location = 0) in vec2 vPos;\n"
			"layout (location = 1) in vec2 uv;\n"
			"out vec2 uvOut;\n"
			"uniform mat4 model;\n"
			"uniform mat4 viewport;\n"
			"void main()\n"
			"{\n"
			"gl_Position = viewport * model * vec4(vPos, 0.0f, 1.0f);\n"
			"uvOut = uv;\n"
			"}\n"
		};

		static constexpr char* geometryFshSrc =
		{
			"#version 330 core\n"
			"in vec2 uvOut;\n"
			"uniform vec4 color;\n"
			"uniform sampler2D textureSampler;\n"
			"uniform bool useTextures;\n"
			"uniform bool enableColorMod;\n"
			"void main()\n"
			"{\n"
			"vec4 fragColor = vec4(1.0f);\n"
			"if (useTextures)\n"
			"{\n"
			"fragColor = texture(textureSampler, uvOut);\n"
			"if (enableColorMod)\n"
			"fragColor *= color;\n"
			"}\n"
			"else\n"
			"fragColor = color;\n"
			"gl_FragColor = fragColor;\n"
			"}\n"
		};

		static constexpr char* textRenderFshSrc =
		{
			"#version 330 core\n"
			"in vec2 uvOut;\n"
			"uniform sampler2D fontAtlasSampler;\n"
			"uniform vec4 textColor;\n"
			"void main()\n"
			"{\n"
			"vec4 texelSample = vec4(1.0f, 1.0f, 1.0f, texture(fontAtlasSampler, uvOut).r);\n"
			"gl_FragColor = texelSample * textColor;\n"
			"}\n"
		};
	}
}

#endif
