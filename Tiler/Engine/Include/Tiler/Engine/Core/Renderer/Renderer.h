#pragma once

#include "glm/glm.hpp"

#include "CameraOrthographic.h"
#include "GraphicsAPI.h"
#include "Shader.h"

#include <memory>


namespace Tiler {

	class Renderer {
	public:
		static void SceneBegin(CameraOrthographic& camera);
		static void SceneEnd();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const glm::mat4& transform = glm::mat4(1.0f));
		inline static GraphicsAPI::Type GetType() { return GraphicsAPI::Static::GetType(); }

	private:
		struct SceneData {
			glm::mat4 MatrixViewProject;
		};

		static SceneData* s_SceneData;
	};
}