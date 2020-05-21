#pragma once

#include "Window.h"
#include "Schmog/Events/ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"


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
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// TO BE DEFINED IN CLIENT
	std::shared_ptr<Application> CreateApplication();

}