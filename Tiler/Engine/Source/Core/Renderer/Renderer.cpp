#include "Tiler/Engine/Core/Renderer/Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace tiler {

	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::sceneBegin(CameraOrthographic& camera) {
		m_sceneData->matrixViewProject = camera.getMatrixViewProjection();
	}

	void Renderer::sceneEnd() {
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuffer,
	    const std::shared_ptr<IndexBuffer>& indexBuffer, const glm::mat4& transfrom) {
		shader->bind();
		shader->setUniform("u_ViewProjection", m_sceneData->matrixViewProject);
		shader->setUniform("u_Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) * transfrom);

		GraphicsAPI::Static::drawIndexed(vertexBuffer, indexBuffer);
	}

}  // namespace tiler