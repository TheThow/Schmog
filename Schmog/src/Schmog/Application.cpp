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

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray = VertexArray::Create();


		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->Bind();

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t indices[3] = {
			0,1,2
		};


		std::shared_ptr<IndexBuffer> m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		m_SquareVA = VertexArray::Create();

		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(vertices2, sizeof(vertices2));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position"}
			});

		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t indices2[6] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(indices2, 6);
		m_SquareVA->SetIndexBuffer(squareIB);
		

		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Position = a_Position;
				v_Color = a_Color;
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;
			in vec4 v_Color;


			void main()
			{
				o_Color = v_Color;
			}

		)";


		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				gl_Position = vec4(a_Position + 0.25, 1.0);
				v_Position = a_Position;
			}

		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;


			void main()
			{
				o_Color = vec4(0.8,0.0,0.8, 1.0);
			}

		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_Shader2.reset(Shader::Create(vertexSrc2, fragmentSrc2));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader2->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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