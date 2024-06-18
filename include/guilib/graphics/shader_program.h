#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <external/glm/glm/glm.hpp>
#include <utilities/libexport.h>
#include <unordered_map>
#include <string>

namespace GUILib
{
	/**
	* @brief This is a class for handing OpenGL shader program operations.
	* Also, make sure that whenever you are using this class you are always allocating it on the heap, not the stack.
	*/
	class LIB_DECLSPEC ShaderProgram
	{
	public:
		/**
		* @brief This is a class constructor method for creating and setting up the OpenGL shader program object.
		* If an error occurs while compiling or linking the shaders, an exception will be thrown with the fetched OpenGL error log message.
		* 
		* @param[in] vshCodeContents - A string containing the source code of the vertex shader.
		* @param[in] fshCodeContents - A string containing the source code of the fragment shader.
		* @param[in] gshCodeContents - A string containing the source code of the geometry shader (this is an optional parameter).
		*/
		ShaderProgram(std::string_view vshSourceCode, std::string_view fshSourceCode, std::string_view gshSourceCode = std::string_view());

		~ShaderProgram();

		/**
		* @brief Assigns a value to the shader uniform specified.
		* 
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] value - The integer value to be assigned to the shader uniform.
		*/
		void SetUniform(const std::string_view& uniformName, int value) const;

		/**
		* @brief Assigns a value to the shader uniform specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] value - The floating-point value to be assigned to the shader uniform.
		*/
		void SetUniform(const std::string_view& uniformName, float value) const;

		/**
		* @brief Assigns a value to the shader uniform specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] value - The boolean value to be assigned to the shader uniform.
		*/
		void SetUniform(const std::string_view& uniformName, bool value) const;

		/**
		* @brief Assigns a vector's values to the shader uniform variable specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] vector - The vector values to be assigned to the shader uniform.
		*/
		void SetUniformGLM(const std::string_view& uniformName, const glm::vec2& vector) const;

		/**
		* @brief Assigns a vector's values to the shader uniform variable specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] vector - The vector values to be assigned to the shader uniform.
		*/
		void SetUniformGLM(const std::string_view& uniformName, const glm::vec3& vector) const;

		/**
		* @brief Assigns a vector's values to the shader uniform variable specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] vector - The vector values to be assigned to the shader uniform.
		*/
		void SetUniformGLM(const std::string_view& uniformName, const glm::vec4& vector) const;

		/**
		* @brief Assigns a matrix's values to the shader uniform variable specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] matrix - The matrix values to be assigned to the shader uniform.
		*/
		void SetUniformGLM(const std::string_view& uniformName, const glm::mat3& matrix) const;

		/**
		* @brief Assigns a matrix's values to the shader uniform variable specified.
		*
		* @param[in] uniformName - A string specifying the name of the shader uniform.
		* @param[in] matrix - The matrix values to be assigned to the shader uniform.
		*/
		void SetUniformGLM(const std::string_view& uniformName, const glm::mat4& matrix) const;

		/**
		* @brief Binds the shader program.
		*/
		void Bind() const;

		/**
		* @brief Unbinds the shader program.
		*/
		void Unbind() const;

		/**
		* @brief Returns the ID of the shader program.
		* @return A unsigned int representing the ID of the shader program.
		*/
		const uint32_t& GetID() const;
	private:
		enum class ShaderOperation
		{
			COMPILATION,
			LINKAGE
		};

		/**
		* @brief Checks whether or not the specified shader operation was successful.
		* An exception is thrown along with the fetched OpenGL error log message if the shader operation failed.
		* 
		* @param[in] id - The id of the shader object or shader program object.
		* @param[in] operation - The type of operation that was executed before the call of this function.
		*/
		void CheckShaderOperationStatus(const uint32_t& id, ShaderOperation operation) const;

		// Returns the location unit of the specified shader uniform variable.
		// The locations of fetched shader uniform are stored in the cache (unordered map) for faster future fetching.

		/**
		* @brief Returns the location unit of the specified shader uniform.
		* The locations of fetched shader uniform are stored in the cache (the unordered map) for faster future lookups.
		* 
		* @param[in] uniformName - The name of the shader uniform to be looked up.
		* @return An integer representing the location unit of the shader uniform if successful, else -1 is returned on failure.
		*/
		int GetUniformLocation(const std::string_view& uniformName) const;
	private:
		uint32_t m_id;
		mutable std::unordered_map<std::string, uint32_t> uniformLocationCache;
	};
}

#endif