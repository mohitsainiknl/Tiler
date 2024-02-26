#include "OpenGLGraphicsAPI.h"

#include "glad/glad.h"

#include "Tiler/Engine/Core/Renderer/VertexArray.h"
#include "Tiler/Engine/Core/Renderer/Buffer/IndexBuffer.h"


namespace Tiler {

	void OpenGLGraphicsAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}