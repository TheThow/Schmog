#include "sgpch.h"
#include "Application.h"

#include "glad/glad.h"


namespace Schmog {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SG_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(Event& e)
	{
		//SG_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SG_BIND_EVENT_FN(Application::OnWindowResize));

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

	void Application::PushOverlay(std::shared_ptr<Layer> layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::PopOverlay(std::shared_ptr<Layer> layer)
	{
		layer->OnDetach();
		m_LayerStack.PopOverlay(layer);
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.6f, 1.0f, 1);
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
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->SetWidth(e.GetWidth());
		m_Window->SetHeight(e.GetHeight());
		return false;
	}
}