#include "Tiler/Engine/Core/Renderer/CameraOrthographic.h"

#include "glm/gtc/matrix_transform.hpp"


namespace Tiler {

	CameraOrthographic::CameraOrthographic(float left, float right, float top, float bottom)
		: m_MatrixView(1.0f) {

		float fov = 45.0f; // Field of view in degrees
		float aspectRatio = 800.0f / 600.0f; // Width / Height
		float nearPlane = 0.1f;
		float farPlane = 100.0f;

		// Calculate the perspective projection matrix
		m_MatrixProjection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

		m_Rotation = { 0.0f, 0.0f, 0.0f };
		m_Position = { 0.0f, 0.0f, 0.0f };

		m_MatrixViewProjection = m_MatrixProjection * m_MatrixView;
	}


	void CameraOrthographic::RecalculateMatrixView() {
		glm::mat4 transform =
			glm::rotate(
				glm::rotate(
					glm::rotate(
						glm::mat4(1.0f),
						glm::radians(m_Rotation.x),
						glm::vec3(1, 0, 0)),
					glm::radians(m_Rotation.y),
					glm::vec3(0, 1, 0)),
				glm::radians(m_Rotation.z),
				glm::vec3(0, 0, 1)
			) *
			glm::translate(glm::mat4(1.0f), m_Position);

		m_MatrixView = glm::inverse(transform);
		m_MatrixViewProjection = m_MatrixProjection * m_MatrixView;
	}

}