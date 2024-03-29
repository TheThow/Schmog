#pragma once

#include "Schmog/Renderer/Camera.h"

namespace Schmog {

	class SceneCamera : public Camera
	{
	public:
		enum class CameraProjectionType { Orthographic = 0, Perspective = 1 };

	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = verticalFov; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		float GetNearClip() const { return m_OrthographicNear; }
		void SetNearClip(float clip) { m_OrthographicNear = clip; RecalculateProjection(); }
		float GetFarClip() const { return m_OrthographicFar; }
		void SetFarClip(float clip) { m_OrthographicFar = clip; RecalculateProjection(); }

		CameraProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(CameraProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }

	protected:
		void RecalculateProjection();

	protected:
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		float m_AspectRatio = 16.f/9.f;
		CameraProjectionType m_ProjectionType = CameraProjectionType::Orthographic;
	};

}