#pragma once

#include <glm/glm.hpp>


namespace Schmog {


	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);


		const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		const glm::mat4& GetViewMatrix() const { return m_View; }

		// Needs to be abstracted for different graphics in future
		glm::mat4 GetVP() const { return m_Projection * m_View; }

		void SetPosition(const glm::vec3 pos) { m_Position = pos; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() const { return m_Position; }
		float getRotation() const { return m_Rotation; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_View;
		glm::mat4 m_Projection;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};


}



