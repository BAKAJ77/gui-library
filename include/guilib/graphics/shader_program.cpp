#include <graphics/shader_program.h>
#include <external/glad/glad.h>
#include <memory>

namespace GUILib
{
	ShaderProgram::ShaderProgram(std::string_view vshSourceCode, std::string_view fshSourceCode, std::string_view gshSourceCode)
	{
		const char* vshSrcCode = vshSourceCode.data();
		const char* fshSrcCode = fshSourceCode.data();
		const char* gshSrcCode = gshSourceCode.data();

		// Compile the given vertex and fragment shader code
		const uint32_t vshID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshID, 1, &vshSrcCode, nullptr);
		glCompileShader(vshID);

		this->CheckShaderOperationStatus(vshID, ShaderOperation::COMPILATION);

		const uint32_t fshID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshID, 1, &fshSrcCode, nullptr);
		glCompileShader(fshID);

		this->CheckShaderOperationStatus(fshID, ShaderOperation::COMPILATION);

		// If a geometry shader has been given, then compile it too
		uint32_t gshID = 0;
		if (!gshSourceCode.empty())
		{
			gshID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(gshID, 1, &gshSrcCode, nullptr);
			glCompileShader(gshID);

			this->CheckShaderOperationStatus(gshID, ShaderOperation::COMPILATION);
		}

		// Create the shader program, then attach the compiled shaders and perform linking operation
		m_id = glCreateProgram();
		glAttachShader(m_id, vshID);
		glAttachShader(m_id, fshID);

		if (gshID > 0) // Attach geometry shader if existing
			glAttachShader(m_id, gshID);

		glLinkProgram(m_id);
		this->CheckShaderOperationStatus(m_id, ShaderOperation::LINKAGE);

		// Cleanup the shader objects, they aren't needed anymore
		glDeleteShader(vshID);
		glDeleteShader(fshID);

		if (gshID > 0) // Cleanup geometry shader if existing
			glDeleteShader(gshID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::CheckShaderOperationStatus(const uint32_t& id, ShaderOperation operation) const
	{
		int operationSuccessful = 0;
		operation == ShaderOperation::COMPILATION ? glGetShaderiv(id, GL_COMPILE_STATUS, &operationSuccessful) :
			glGetProgramiv(id, GL_LINK_STATUS, &operationSuccessful);

		if (!operationSuccessful)
		{
			std::unique_ptr<char> errorLog;
			int logLength = 0;

			// Get the shader error log message information
			switch (operation)
			{
			case ShaderOperation::COMPILATION:
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
				errorLog = std::unique_ptr<char>(new char[logLength]);
				glGetShaderInfoLog(id, logLength, nullptr, errorLog.get());
				break;
			case ShaderOperation::LINKAGE:
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
				errorLog = std::unique_ptr<char>(new char[logLength]);
				glGetProgramInfoLog(id, logLength, nullptr, errorLog.get());
				break;
			}

			throw std::exception(errorLog.get());
		}
	}

	int ShaderProgram::GetUniformLocation(const std::string_view& uniformName) const
	{
		auto cacheIterator = this->uniformLocationCache.find(uniformName.data()); // Check if location is already cached
		if (cacheIterator == this->uniformLocationCache.end())
		{
			// It is not cached so fetch it from GPU, store it in cache and return it
			const int location = glGetUniformLocation(m_id, uniformName.data());
			if (location > 0) // Lookup was successful
				this->uniformLocationCache[uniformName.data()] = (uint32_t)location;

			return location;
		}

		return (int)cacheIterator->second; // The location was found in cache
	}

	void ShaderProgram::SetUniform(const std::string_view& uniformName, int value) const
	{
		glUniform1i(this->GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string_view& uniformName, float value) const
	{
		glUniform1f(this->GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string_view& uniformName, bool value) const
	{
		glUniform1i(this->GetUniformLocation(uniformName), (int)value);
	}

	void ShaderProgram::SetUniformGLM(const std::string_view& uniformName, const glm::vec2& vector) const
	{
		glUniform2fv(this->GetUniformLocation(uniformName), 1, &vector[0]);
	}

	void ShaderProgram::SetUniformGLM(const std::string_view& uniformName, const glm::vec3& vector) const
	{
		glUniform3fv(this->GetUniformLocation(uniformName), 1, &vector[0]);
	}

	void ShaderProgram::SetUniformGLM(const std::string_view& uniformName, const glm::vec4& vector) const
	{
		glUniform4fv(this->GetUniformLocation(uniformName), 1, &vector[0]);
	}

	void ShaderProgram::SetUniformGLM(const std::string_view& uniformName, const glm::mat3& matrix) const
	{
		glUniformMatrix3fv(this->GetUniformLocation(uniformName), 1, false, &matrix[0][0]);
	}

	void ShaderProgram::SetUniformGLM(const std::string_view& uniformName, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(this->GetUniformLocation(uniformName), 1, false, &matrix[0][0]);
	}

	void ShaderProgram::Bind() const { glUseProgram(m_id); }

	void ShaderProgram::Unbind() const { glUseProgram(0); }

	const uint32_t& ShaderProgram::GetID() const { return m_id; }
}