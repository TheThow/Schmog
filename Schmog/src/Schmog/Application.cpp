#include "sgpch.h"
#include "Application.h"
#include "Platform/Platform.h"


namespace Schmog {


	Application* Application::s_Instance = nullptr;
	const float Application::DELTA_TIME = 0.0166f;


	Application::Application()
	{
		SG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(SG_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);

		m_LastFrameTime = Platform::GetTime();
		m_Window->SetVSync(false);
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SG_BIND_EVENT_FN(Application::OnWindowResize));

		if (!e.Handled)
		{
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
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
			float time = (float) Platform::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Accumulator += timestep;

			while (m_Accumulator >= DELTA_TIME)
			{
				for (auto ptr = m_LayerStack.begin(); ptr < m_LayerStack.end(); ptr++)
				{
					(*ptr)->OnUpdate();
				}

				m_ImGuiLayer->Begin();
				for (auto ptr = m_LayerStack.begin(); ptr < m_LayerStack.end(); ptr++)
				{
					(*ptr)->OnImGuiRender();
				}
				m_ImGuiLayer->End();

				m_Window->OnUpdate();

				m_Accumulator -= DELTA_TIME;
			}

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->OnWindowResize();
		return false;
	}
}