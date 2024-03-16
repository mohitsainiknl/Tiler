#include "Tiler/Engine/Core/Renderer/CameraOrthographic.h"

#include "glm/gtc/matrix_transform.hpp"

namespace tiler {

	CameraOrthographic::CameraOrthographic(float left, float right, float top, float bottom) : m_matrixView(1.0f) {
		float fov         = 45.0f;            // Field of view in degrees
		float aspectRatio = 800.0f / 600.0f;  // Width / Height
		float nearPlane   = 0.1f;
		float farPlane    = 100.0f;

		// Calculate the perspective projection matrix
		m_matrixProjection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

		m_rotation = {0.0f, 0.0f, 0.0f};
		m_position = {0.0f, 0.0f, 0.0f};

		m_matrixViewProjection = m_matrixProjection * m_matrixView;
	}

	void CameraOrthographic::recalculateMatrixView() {
		glm::mat4 transform =
		    glm::rotate(glm::rotate(glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0)),
		                    glm::radians(m_rotation.y), glm::vec3(0, 1, 0)),
		        glm::radians(m_rotation.z), glm::vec3(0, 0, 1)) *
		    glm::translate(glm::mat4(1.0f), m_position);

		m_matrixView           = glm::inverse(transform);
		m_matrixViewProjection = m_matrixProjection * m_matrixView;
	}

}  // namespace tiler