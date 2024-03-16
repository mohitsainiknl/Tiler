#pragma once

#include "glm/glm.hpp"

namespace tiler {

	class CameraOrthographic {
	public:
		CameraOrthographic(float left, float right, float top, float bottom);

		const glm::vec3& getPosition() const { return m_position; }
		const glm::vec3& getRotation() const { return m_rotation; }

		void setPosition(const glm::vec3& position) {
			m_position = position;
			recalculateMatrixView();
		}
		void setRotation(const glm::vec3& rotation) {
			m_rotation = rotation;
			recalculateMatrixView();
		}

		const glm::mat4& getMatrixView() const { return m_matrixView; }
		const glm::mat4& getMatrixProjection() const { return m_matrixProjection; }
		const glm::mat4& getMatrixViewProjection() const { return m_matrixViewProjection; }

	private:
		void recalculateMatrixView();

	private:
		glm::mat4 m_matrixView;
		glm::mat4 m_matrixProjection;
		glm::mat4 m_matrixViewProjection;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
	};

}  // namespace tiler