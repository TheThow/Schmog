#include "EditorLayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

#include <iostream>


namespace Schmog {


	void SchmeditorLayer::OnAttach()
	{
		auto& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 18.0f);

		FrameBufferSpec fbSpec;
		fbSpec.Attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::Depth };
		fbSpec.Width = 1600;
		fbSpec.Height = 900;

		m_FrameBuffer = FrameBuffer::Create(fbSpec);

		auto cam = m_ActiveScene->CreateEntity("Cam");
		cam.AddComponent<CameraComponent>();

		auto cam2 = m_ActiveScene->CreateEntity("Cam 2");
		cam2.AddComponent<CameraComponent>();

		auto square = m_ActiveScene->CreateEntity("Red square");
		square.AddComponent<SpriteRendererComponent>(RGBa(255, 0, 0, 255));

		auto square2 = m_ActiveScene->CreateEntity("Yellow square");
		square2.AddComponent<SpriteRendererComponent>(RGBa(255, 255, 0, 255));
		square2.GetComponent<TransformComponent>().Position.x += 3;
		square2.GetComponent<TransformComponent>().Scale *= 2;

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void SchmeditorLayer::OnDetach()
	{
	}

	void SchmeditorLayer::OnUpdate()
	{
		Schmog::Renderer2D::ResetStats();

		m_FrameBuffer->Bind();
		Schmog::RenderCommand::Clear();

		m_ActiveScene->OnUpdateEditor(m_EditorCamera);

		if (m_ViewportFocused)
			m_EditorCamera.OnUpdate();

		m_FrameBuffer->Unbind();
	}

	void SchmeditorLayer::OnImGuiRender()
	{
		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;


		ImGui::Begin("DockSpace Editor", &dockspaceOpen, window_flags);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");

		auto stats = Schmog::Renderer2D::GetStats();

		ImGui::Text("Draw Calls: %i", stats.drawCalls);
		ImGui::Text("Quads: %i", stats.quadCount);
		ImGui::Text("");
		ImGui::Text("Application average");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		if (m_ViewportSize != glm::vec2(viewportPanelSize.x, viewportPanelSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_EditorCamera.SetViewportSize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)(uint64_t)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::End();
	}

	void SchmeditorLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(SG_BIND_EVENT_FN(SchmeditorLayer::OnKeyPressed));
		m_EditorCamera.OnEvent(e);
	}

	bool SchmeditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(KeyCode::LeftControl) || Input::IsKeyPressed(KeyCode::RightControl);
		bool shift = Input::IsKeyPressed(KeyCode::LeftShift) || Input::IsKeyPressed(KeyCode::RightShift);
		switch (e.GetKeyCode())
		{
			case KeyCode::N:
			{
				if (control)
					NewScene();

				break;
			}
			case KeyCode::O:
			{
				if (control)
					OpenScene();

				break;
			}
			case KeyCode::S:
			{
				if (control && shift)
					SaveSceneAs();

				break;
			}
		}

		return false;
	}

	void SchmeditorLayer::NewScene()
	{
		m_ActiveScene = std::make_shared<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void SchmeditorLayer::OpenScene()
	{
		std::optional<std::string> filepath = FileDialogs::OpenFile("Schmog Scene (*.schmog)\0*.schmog\0");
		if (filepath)
		{
			m_ActiveScene = std::make_shared<Scene>();
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);
			m_ActiveScene->Deserialize(*filepath);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
	}

	void SchmeditorLayer::SaveSceneAs()
	{
		std::optional<std::string> filepath = FileDialogs::SaveFile("Schmog Scene (*.schmog)\0*.schmog\0");
		if (filepath)
		{
			m_ActiveScene->Serialize(*filepath);
		}
	}
}