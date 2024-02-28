#pragma once

#include "Tiler/Engine/Core/Renderer/Shader.h"

#include <unordered_map>


namespace Tiler {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetUniform(const std::string& name, int value) override;
		void SetUniform(const std::string& name, float value) override;
		void SetUniform(const std::string& name, const glm::vec3& value) override;
		void SetUniform(const std::string& name, const glm::mat4& value) override;

	private:
		int GetUniformLocation(const std::string& name);

		uint32_t m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}