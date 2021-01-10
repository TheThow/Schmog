#pragma once

#include <memory>

#include "Schmog.h"
#include "Panels/SceneHierachyPanel.h"

#include "Schmog/Utils/PlatformUtils.h"

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

		bool SchmeditorLayer::OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		std::shared_ptr<Scene> m_ActiveScene;
		SceneHierachyPanel m_SceneHierarchyPanel;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		glm::vec2 m_ViewportSize;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

		EditorCamera m_EditorCamera;
	};

}