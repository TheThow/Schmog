#include <Schmog.h>
#include <memory>

#include <imgui/imgui.h>


class ExampleLayer : public Schmog::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CamPos(0.0f)
	{
		using namespace Schmog;
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



		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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


		std::string squareVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position + 0.25, 1.0);
				v_Position = a_Position;
			}

		)";

		std::string squareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;


			void main()
			{
				o_Color = vec4(0.8,0.0,0.8, 1.0);
			}

		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_Shader2.reset(Shader::Create(squareVertexSrc, squareFragmentSrc));

		m_Camera = std::make_shared<OrthographicCamera>(-1.6f, 1.6f, -.9f, .9f);
	}

	void OnUpdate()
	{
		if (Schmog::Input::IsKeyPressed(SG_KEY_DOWN))
		{
			m_CamPos.y -= m_CamSpeed;
		}
		if (Schmog::Input::IsKeyPressed(SG_KEY_UP))
		{
			m_CamPos.y += m_CamSpeed;
		}
		if (Schmog::Input::IsKeyPressed(SG_KEY_LEFT))
		{
			m_CamPos.x -= m_CamSpeed;
		}
		if (Schmog::Input::IsKeyPressed(SG_KEY_RIGHT))
		{
			m_CamPos.x += m_CamSpeed;
		}

		m_Camera->SetPosition(m_CamPos);

		Schmog::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Schmog::RenderCommand::Clear();

		Schmog::Renderer::BeginScene(m_Camera);

		Schmog::Renderer::Submit(m_Shader2, m_SquareVA);

		Schmog::Renderer::Submit(m_Shader, m_VertexArray);

		Schmog::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
		

	void OnEvent(Schmog::Event& e)
	{
		//SG_TRACE("{0} - {1}", m_DebugName, e);
	}



private:
	std::shared_ptr<Schmog::Shader> m_Shader;
	std::shared_ptr<Schmog::Shader> m_Shader2;

	std::shared_ptr<Schmog::VertexArray> m_VertexArray;
	std::shared_ptr<Schmog::VertexArray> m_SquareVA;
	std::shared_ptr<Schmog::OrthographicCamera> m_Camera;

	glm::vec3 m_CamPos;
	float m_CamSpeed = 0.1f;
};


class Sandbox : public Schmog::Application
{
public: 
	Sandbox()
	{
		PushLayer(std::make_shared<ExampleLayer>());
	}

	~Sandbox() 
	{

	}


};

std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
{
	return std::make_shared<Sandbox>();
}