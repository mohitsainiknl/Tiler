#include "OpenGLGraphicsAPI.h"

#include "glad/glad.h"


namespace Tiler {

	void OpenGLGraphicsAPI::DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) {
		vertexBuffer->Bind();
		indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}