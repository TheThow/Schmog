#include "sgpch.h"
#include "CameraController.h"

#include "Schmog/Core/Input.h"
#include "Schmog/Core/KeyCodes.h"

namespace Schmog {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}


	void OrthographicCameraController::OnUpdate()
	{
		if (Input::IsKeyPressed(SG_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed;
		}
		if (Input::IsKeyPressed(SG_KEY_UP))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed;
		}
		if (Input::IsKeyPressed(SG_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed;
		}
		if (Input::IsKeyPressed(SG_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel / 20.0f;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SG_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(SG_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizeEvent));
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_ZoomLevel += e.GetYOffset() * -0.25f;

		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 100.0f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}


}
