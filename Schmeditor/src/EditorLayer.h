#pragma once

#include <memory>

#include "Schmog.h"
#include "Panels/SceneHierachyPanel.h"

namespace Schmog {

	class SchmeditorLayer : public Layer
	{

	public:
		SchmeditorLayer()
			: Layer("Schmeditor"), m_ActiveScene(new Scene())
		{

		}
		~SchmeditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		std::shared_ptr<Scene> m_ActiveScene;
		SceneHierachyPanel m_SceneHierachyPanel;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		glm::vec2 m_ViewportSize;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

	};

}