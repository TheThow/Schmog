#include "sgpch.h"
#include "Application.h"

#include "glad/glad.h"


namespace Schmog {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(Event& e)
	{
		//SG_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		if (!e.Handled)
		{
			for (auto it = m_LayerStack.End(); it != m_LayerStack.Begin(); )
			{
				(*--it)->OnEvent(e);
				if (e.Handled)
					break;
			}
		}
	}

	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(std::shared_ptr<Layer> layer)
	{
		layer->OnDetach();
		m_LayerStack.PopLayer(layer);
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto ptr = m_LayerStack.Begin(); ptr < m_LayerStack.End(); ptr++)
			{
				(*ptr)->OnUpdate();
			}

			m_Window->OnUpdate();
			
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}