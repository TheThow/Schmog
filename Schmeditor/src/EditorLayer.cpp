#include "EditorLayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

#include <iostream>


namespace Schmog {

	class CameraController : public NativeScript
	{
		void OnUpdate() override {
			auto& transform = GetComponent<TransformComponent>();

			if (Input::IsKeyPressed(KeyCode::Down))
			{
				transform.Position.y -= 0.5f;
			}
			if (Input::IsKeyPressed(KeyCode::Up))
			{
				transform.Position.y += 0.5f;
			}
			if (Input::IsKeyPressed(KeyCode::Left))
			{
				transform.Position.x -= 0.5f;
			}
			if (Input::IsKeyPressed(KeyCode::Right))
			{
				transform.Position.x += 0.5f;
			}

		}
	};

	void SchmeditorLayer::OnAttach()
	{
		FrameBufferSpec fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);

		auto cam = m_ActiveScene->CreateEntity("Cam");
		cam.AddComponent<CameraComponent>();
		cam.AddComponent<NativeScriptingComponent>().Bind<CameraController>();

		auto cam2 = m_ActiveScene->CreateEntity("Cam 2");
		cam2.AddComponent<CameraComponent>();

		auto square = m_ActiveScene->CreateEntity("Red square");
		square.AddComponent<SpriteRendererComponent>(RGBa(255, 0, 0, 255));

		auto square2 = m_ActiveScene->CreateEntity("Yellow square");
		square2.AddComponent<SpriteRendererComponent>(RGBa(255, 255, 0, 255));
		square2.GetComponent<TransformComponent>().Position.x += 3;
		square2.GetComponent<TransformComponent>().Scale *= 2;

		m_SceneHierachyPanel.SetContext(m_ActiveScene);
	}

	void SchmeditorLayer::OnDetach()
	{
	}

	void SchmeditorLayer::OnUpdate()
	{
		Schmog::Renderer2D::ResetStats();

		m_FrameBuffer->Bind();
		Schmog::RenderCommand::Clear();

		m_ActiveScene->OnUpdate();

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

		m_SceneHierachyPanel.OnImGuiRender();

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		if (m_ViewportSize != glm::vec2(viewportPanelSize.x, viewportPanelSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)(uint64_t)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::End();
	}

	void SchmeditorLayer::OnEvent(Event& e)
	{
	}
}