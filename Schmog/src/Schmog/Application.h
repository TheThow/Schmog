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

		void Run();

		void OnEvent(Event& e);

		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;
	};

	// TO BE DEFINED IN CLIENT
	std::shared_ptr<Application> CreateApplication();

}