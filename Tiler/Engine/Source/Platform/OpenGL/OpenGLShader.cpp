#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "Tiler/Engine/Base.h"

namespace tiler {

	static uint32_t CompileShader(uint32_t type, const std::string& source);
	static uint32_t LinkProgram(uint32_t program, uint32_t vert_shader, uint32_t frag_shader);

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
		uint32_t vert_shader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		uint32_t frag_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		m_rendererID = glCreateProgram();
		LinkProgram(m_rendererID, vert_shader, frag_shader);

		glDetachShader(m_rendererID, vert_shader);
		glDetachShader(m_rendererID, frag_shader);
	}

	OpenGLShader::~OpenGLShader() {
		unbind();
	}

	void OpenGLShader::bind() const {
		glUseProgram(m_rendererID);
	}

	void OpenGLShader::unbind() const {
		glDeleteProgram(m_rendererID);
	}

	void OpenGLShader::setUniform(const std::string& name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void OpenGLShader::setUniform(const std::string& name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void OpenGLShader::setUniform(const std::string& name, const glm::vec3& value) {
		glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	int OpenGLShader::getUniformLocation(const std::string& name) {
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
			return m_uniformLocationCache.at(name);
		}

		const int location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) {
			TL_CORE_WARN("Warning: Uniform {0} doesn't exist!", name);
		}

		m_uniformLocationCache["name"] = location;
		return location;
	}

	static uint32_t CompileShader(uint32_t type, const std::string& source) {
		const uint32_t shader = glCreateShader(type);
		const char* src       = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			int log_length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

			std::vector<char> info_log(log_length);
			glGetShaderInfoLog(shader, log_length, &log_length, &info_log[0]);

			TL_CORE_DEBUG("Shader Code:\n" + source);

			TL_CORE_ERROR("{0} shader compilation failure!\n"
			              "	{1}",
			    (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), info_log.data());

			TL_DEBUG_BREAK();

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	static uint32_t LinkProgram(uint32_t program, uint32_t vert_shader, uint32_t frag_shader) {
		glAttachShader(program, vert_shader);
		glAttachShader(program, frag_shader);
		glLinkProgram(program);
		glValidateProgram(program);

		int success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			int log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

			std::vector<char> info_log(log_length);
			glGetProgramInfoLog(program, log_length, &log_length, &info_log[0]);

			TL_CORE_ERROR("Shader program linking failure!\n"
			              "	{0}",
			    info_log.data());

			TL_DEBUG_BREAK();

			glDeleteProgram(program);
			return 0;
		}
	}

}  // namespace tiler