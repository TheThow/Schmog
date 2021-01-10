#pragma once

#include "SceneCamera.h"
#include "Schmog/Events/MouseEvent.h"
#include "Schmog/Events/Event.h"

namespace Schmog {

	class EditorCamera : public SceneCamera
	{
	public:
		EditorCamera();

		void OnUpdate();
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		const glm::vec3& GetPosition() const { return m_Position; }

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

	private:
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnMouseReleased(MouseButtonReleasedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);

		void MousePan(const glm::vec2& delta);

		void MouseZoom(float delta);

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;

		glm::mat4 m_ViewMatrix;
 	};

}