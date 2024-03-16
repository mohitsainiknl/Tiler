#pragma once

#include "glm/glm.hpp"

#include <string>

namespace tiler {

	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;

		virtual void bind() const   = 0;
		virtual void unbind() const = 0;

		virtual void setUniform(const std::string& name, int value)              = 0;
		virtual void setUniform(const std::string& name, float value)            = 0;
		virtual void setUniform(const std::string& name, const glm::vec3& value) = 0;
		virtual void setUniform(const std::string& name, const glm::mat4& value) = 0;

		static Shader* create(const std::string& vertexSource, const std::string& fragmentSource);

	protected:
		Shader() = default;
	};

}  // namespace tiler