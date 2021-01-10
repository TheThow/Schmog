#include "sgpch.h"
#include "EditorCamera.h"
#include "Schmog/Core/Input.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Schmog {

	EditorCamera::EditorCamera()
	{
		RecalculateProjection();
		UpdateView();
	}

	void EditorCamera::UpdateView()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}


	void EditorCamera::OnUpdate()
	{
		if (Input::IsKeyPressed(KeyCode::LeftControl))
		{
			const glm::vec2& mouse{ Input::GetMousePosition().x, Input::GetMousePosition().y };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(MouseButtonCode::ButtonRight))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(MouseButtonCode::ButtonMiddle))
				MouseZoom(delta.y);
		}

		float fac = m_OrthographicSize / 50.0f;
		if (Input::IsKeyPressed(KeyCode::Down))
		{
			m_Position.y -= fac;
		}
		if (Input::IsKeyPressed(KeyCode::Up))
		{
			m_Position.y += fac;
		}
		if (Input::IsKeyPressed(KeyCode::Left))
		{
			m_Position.x -= fac;
		}
		if (Input::IsKeyPressed(KeyCode::Right))
		{
			m_Position.x += fac;
		}

		UpdateView();
		RecalculateProjection();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SG_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
		dispatcher.Dispatch<MouseButtonPressedEvent>(SG_BIND_EVENT_FN(EditorCamera::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(SG_BIND_EVENT_FN(EditorCamera::OnMouseReleased));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	bool EditorCamera::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		return false;
	}

	bool EditorCamera::OnMousePressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == MouseButtonCode::ButtonRight)
		{
			m_InitialMousePosition = { Input::GetMousePosition().x, Input::GetMousePosition().y };
		}

		return false;
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		float factor = m_OrthographicSize / 5.0f;
		m_Position -= glm::vec3{ delta.x * factor, delta.y * -factor, 0.0f };
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_OrthographicSize -= delta * 10.0f;
	}

}

