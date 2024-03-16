#pragma once

#include "Tiler/Engine/Core/Renderer/Shader.h"

#include <unordered_map>

namespace tiler {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		void bind() const override;
		void unbind() const override;

		void setUniform(const std::string& name, int value) override;
		void setUniform(const std::string& name, float value) override;
		void setUniform(const std::string& name, const glm::vec3& value) override;
		void setUniform(const std::string& name, const glm::mat4& value) override;

	private:
		int getUniformLocation(const std::string& name);

		uint32_t m_rendererID;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};

}  // namespace tiler