#pragma once

#include "Tiler/Engine/Core/Renderer/RenderCommand.h"

#include <memory>

namespace Tiler {
	class CameraOrthographic;
	class Shader;
}

namespace Tiler {

	class Renderer {
	public:
		static void SceneBegin(CameraOrthographic& camera);
		static void SceneEnd();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 MatrixViewProject;
		};

		static SceneData* s_SceneData;
	};
}