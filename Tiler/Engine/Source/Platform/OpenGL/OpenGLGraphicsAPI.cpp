#include "OpenGLGraphicsAPI.h"

#include "glad/glad.h"

namespace tiler {

	void OpenGLGraphicsAPI::drawIndexed(
	    const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) {
		vertexBuffer->bind();
		indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}  // namespace tiler