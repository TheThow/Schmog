#pragma once

#include "Camera.h"

#include "Schmog/Events/ApplicationEvent.h"
#include "Schmog/Events/MouseEvent.h"

namespace Schmog {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate();
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		void SetZoomLevel(float level);
		float GetZoomLevel() const { return m_ZoomLevel; }
		float GetAspectRatio() const { return m_AspectRatio; }

		void OnResize(const uint32_t width, const uint32_t height);

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		void Update();

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 0.05f, m_CameraRotationSpeed = 1.0f;
	};

}


