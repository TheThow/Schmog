#include "Sandbox2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

void Sandbox2D::OnAttach()
{
	using namespace Schmog;

	m_VA = VertexArray::Create();

	float vertices2[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		0.5f,  0.5f,  0.0f, 
		-0.5f, 0.5f,  0.0f,
	};
	std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(vertices2, sizeof(vertices2));

	vb->SetLayout({
		{ ShaderDataType::Float3, "a_Position"}
		});

	m_VA->AddVertexBuffer(vb);
	uint32_t indices2[6] = {
		0,1,2,
		2,3,0
	};
	std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(indices2, 6);
	m_VA->SetIndexBuffer(ib);

	m_Shader = Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate()
{
	m_Camera.OnUpdate();

	//Render
	Schmog::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Schmog::RenderCommand::Clear();

	Schmog::Renderer::BeginScene(m_Camera.GetCamera());

	float fac = 0.5;

	auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(fac));


	m_Shader->Bind();

	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			auto transform = rot * glm::translate(glm::mat4(1.0f), glm::vec3(fac * x, fac * y, 0)) * scale;
			m_Shader->SetUniform("u_Color", glm::vec4(m_Color1, 1.0f));
			Schmog::Renderer::Submit(m_Shader, m_VA, transform);
		}

	}

	Schmog::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_Color1));
	ImGui::End();
}

void Sandbox2D::OnEvent(Schmog::Event& e)
{
	m_Camera.OnEvent(e);
}
