#include <Schmog.h>
// ------ ENTRY POINT ------
#include "Schmog/EntryPoint.h"
#include <memory>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.inl>

#include "Sandbox2D.h"

class ExampleLayer : public Schmog::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_SquareTransform(glm::mat4(1.0f)), m_Camera(16.f / 9.f)
	{
		
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
		//PushLayer(std::make_shared<ExampleLayer>());
		PushLayer(std::make_shared<Sandbox2D>());
	}

	~Sandbox() 
	{

	}


};

std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
{
	return std::make_shared<Sandbox>();
}