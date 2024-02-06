#include "Tiler/Renderer/Renderer.h"

#include "Tiler/Renderer/VertexArray.h"
#include "Tiler/Renderer/CameraOrthographic.h"
#include "Tiler/Renderer/Shader.h"


namespace Tiler {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::SceneBegin(CameraOrthographic& camera) {
		s_SceneData->MatrixViewProject = camera.GetMatrixViewProjection();
	}


	void Renderer::SceneEnd() {

	}


	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->MatrixViewProject);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}