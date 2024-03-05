#pragma once

#include "glm/glm.hpp"

namespace Tiler {

	class CameraOrthographic {
	public:
		CameraOrthographic(float left, float right, float top, float bottom);

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMatrixView(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateMatrixView(); }

		const glm::mat4& GetMatrixView()            const { return m_MatrixView; }
		const glm::mat4& GetMatrixProjection()      const { return m_MatrixProjection; }
		const glm::mat4& GetMatrixViewProjection()  const { return m_MatrixViewProjection; }

	private:
		void RecalculateMatrixView();

	private:
		glm::mat4 m_MatrixView;
		glm::mat4 m_MatrixProjection;
		glm::mat4 m_MatrixViewProjection;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};

}