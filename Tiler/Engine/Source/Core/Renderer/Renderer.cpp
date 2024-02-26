#include "Tiler/Engine/Core/Renderer/Renderer.h"



namespace Tiler {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::SceneBegin(CameraOrthographic& camera) {
		s_SceneData->MatrixViewProject = camera.GetMatrixViewProjection();
	}


	void Renderer::SceneEnd() {

	}


	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transfrom) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->MatrixViewProject);
		shader->UploadUniformMat4("u_Transform", transfrom);

		vertexArray->Bind();
		GraphicsAPI::Static::DrawIndexed(vertexArray);
	}

}