#pragma once

#include "Core.h"

#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Schmog/Events/Event.h"
#include "Schmog/Events/ApplicationEvent.h"

#include "Schmog/ImGui/ImGuiLayer.h"
#include "Schmog/Renderer/Shader.h"
#include "Schmog/Renderer/Buffer.h"
#include "Schmog/Renderer/VertexArray.h"


namespace Schmog {

	class SCHMOG_API Application
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);

		void PushOverlay(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }



	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;

		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_Shader2;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;
	};

	// TO BE DEFINED IN CLIENT
	std::shared_ptr<Application> CreateApplication();

}