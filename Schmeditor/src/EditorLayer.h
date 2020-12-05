#pragma once

#include <memory>

#include "Schmog.h"

namespace Schmog {

	class ScheditorLayer : public Layer
	{

	public:
		ScheditorLayer()
			: Layer("Scheditor"), m_Camera(16.f / 9.f)
		{

		}
		~ScheditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_Camera;

		Scene m_ActiveScene;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		glm::vec2 m_ViewportSize;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

	};

}