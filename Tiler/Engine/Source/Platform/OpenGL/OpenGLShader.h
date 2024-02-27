#pragma once

#include "Tiler/Engine/Core/Renderer/Shader.h"


namespace Tiler {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;
	};

}