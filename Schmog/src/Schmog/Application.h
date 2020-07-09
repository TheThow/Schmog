#pragma once

#include "Core/Core.h"

#include "Core/Window.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Schmog/Events/Event.h"
#include "Schmog/Events/ApplicationEvent.h"

#include "Schmog/ImGui/ImGuiLayer.h"
#include "Schmog/Renderer/Shader.h"
#include "Schmog/Renderer/Buffer.h"
#include "Schmog/Renderer/VertexArray.h"

#include "Schmog/Core/Timestep.h"
#include "Schmog/Game/ParticleSystem.h"


namespace Schmog {

	class SCHMOG_API Application
	{
	public:
		Application(const std::string& name = "Schmog App");
		virtual ~Application();

		Application(const Application&) = delete;

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);

		void PushOverlay(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> layer);

		std::shared_ptr<ImGuiLayer> GetImGuiLayer();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
		std::shared_ptr<ParticleSystem> GetParticleSystem() { return m_ParticleSystem; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;

		std::shared_ptr<ParticleSystem> m_ParticleSystem;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime;
		float m_Accumulator = 0.0f;

	private:
		static Application* s_Instance;
		static const float DELTA_TIME;
	};

	// TO BE DEFINED IN CLIENT
	std::shared_ptr<Application> CreateApplication();

}