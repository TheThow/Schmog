#pragma once

#include <memory>

#include "Schmog.h"

namespace Schmog {

	class SchmeditorLayer : public Layer
	{

	public:
		SchmeditorLayer()
			: Layer("Schmeditor")
		{

		}
		~SchmeditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		Scene m_ActiveScene;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		glm::vec2 m_ViewportSize;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

	};

}