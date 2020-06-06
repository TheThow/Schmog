#include <Schmog.h>
#include <memory>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.inl>


class ExampleLayer : public Schmog::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_SquareTransform(glm::mat4(1.0f)), m_Camera(16.f / 9.f)
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

		float vertices2[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(vertices2, sizeof(vertices2));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TexCoords"}
			});

		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t indices2[6] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(indices2, 6);
		m_SquareVA->SetIndexBuffer(squareIB);

		m_ShaderLib = std::make_shared<Schmog::ShaderLibrary>();
		auto texShader = m_ShaderLib->Load("assets/shaders/Texture.glsl");

		m_Texture = Schmog::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture->Bind(0);
		texShader->Bind();
		texShader->SetUniform("u_Texture", 0);
	}

	void OnUpdate()
	{
		//Update
		m_Camera.OnUpdate();

		//Render
		Schmog::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Schmog::RenderCommand::Clear();

		Schmog::Renderer::BeginScene(m_Camera.GetCamera());

		float fac = 0.5;

		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(m_SquareRot), glm::vec3(0, 0, 1));
		auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(fac));


		auto texShader = m_ShaderLib->Get("Texture");
		texShader->Bind();
		m_Texture->Bind();

		for (int y = -10; y <= 10; y++)
		{
			for (int x = -10; x <= 10; x++)
			{
				m_SquareTransform = rot * glm::translate(glm::mat4(1.0f), glm::vec3(fac * x, fac * y, 0)) * scale;
				texShader->SetUniform("u_Color", glm::vec4(m_Color1, 1.0f));
				m_Texture->Bind();
				Schmog::Renderer::Submit(texShader, m_SquareVA, m_SquareTransform);
			}

		}

		Schmog::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_Color1));
		ImGui::End();
	}
		

	void OnEvent(Schmog::Event& e)
	{
		m_Camera.OnEvent(e);
		//SG_TRACE("{0} - {1}", m_DebugName, e);
	}



private:
	std::shared_ptr<Schmog::ShaderLibrary> m_ShaderLib;

	std::shared_ptr<Schmog::Texture2D> m_Texture;

	std::shared_ptr<Schmog::VertexArray> m_VertexArray;
	std::shared_ptr<Schmog::VertexArray> m_SquareVA;


	Schmog::OrthographicCameraController m_Camera;

	glm::mat4 m_SquareTransform;
	float m_SquareRot = 0.0f;
	float m_SquareRotSpeed = 2.0f;

	glm::vec3 m_Color1 = { 0.8f, 0.2f, 0.8f};
	glm::vec3 m_Color2 = { 0.2f, 0.3f, 0.8f};


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