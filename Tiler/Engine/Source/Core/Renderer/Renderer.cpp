#include "Tiler/Engine/Core/Renderer/Renderer.h"



namespace Tiler {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::SceneBegin(CameraOrthographic& camera) {
		s_SceneData->MatrixViewProject = camera.GetMatrixViewProjection();
	}


	void Renderer::SceneEnd() {

	}


	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const glm::mat4& transfrom) {
		shader->Bind();
		shader->SetUniform("u_ViewProjection", s_SceneData->MatrixViewProject);
		shader->SetUniform("u_Transform", transfrom);

		GraphicsAPI::Static::DrawIndexed(vertexBuffer, indexBuffer);
	}

}