#include "Tiler/Renderer/Renderer.h"

#include "Tiler/Renderer/VertexArray.h"


namespace Tiler {

	void Renderer::SceneBegin() {

	}


	void Renderer::SceneEnd() {

	}


	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}