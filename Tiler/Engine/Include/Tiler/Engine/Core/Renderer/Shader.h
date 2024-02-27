#pragma once

#include "glm/glm.hpp"

#include <string>


namespace Tiler {

	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);

	protected:
		Shader() = default;
	};

}