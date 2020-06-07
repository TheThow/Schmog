#include "Sandbox2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

void Sandbox2D::OnAttach()
{
	m_Texture = Schmog::Texture2D::Create("assets/textures/Checkerboard.png");
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

	Schmog::Renderer2D::BeginScene(m_Camera.GetCamera());

	float fac = 0.5f;

	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			Schmog::Renderer2D::DrawQuad({ fac * 1.1 * x, fac * 1.1 * y}, { fac, fac }, m_Texture, { m_Color1, 1.0f });
		}
	}

	Schmog::Renderer2D::EndScene();

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
