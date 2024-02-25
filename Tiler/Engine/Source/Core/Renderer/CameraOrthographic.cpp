#include "Tiler/Engine/Core/Renderer/CameraOrthographic.h"

#include "glm/gtc/matrix_transform.hpp"


namespace Tiler {

	CameraOrthographic::CameraOrthographic(float left, float right, float top, float bottom)
		: m_MatrixProjection(glm::ortho(left, right, top, bottom, -1.0f, 1.0f)), m_MatrixView(1.0f) {

		m_Rotation = 0.0f;
		m_Position = { 0.0f, 0.0f, 0.0f };

		m_MatrixViewProjection = m_MatrixProjection * m_MatrixView;
	}


	void CameraOrthographic::RecalculateMatrixView() {
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate   (glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_MatrixView = glm::inverse(transform);
		m_MatrixViewProjection = m_MatrixProjection * m_MatrixView;
	}

}