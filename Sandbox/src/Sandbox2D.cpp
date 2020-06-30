#include "Sandbox2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

#include <iostream>




void Sandbox2D::OnAttach()
{
	m_Texture = Schmog::Texture2D::Create("assets/textures/Checkerboard.png");

	m_ParticleProps.StartColor = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_ParticleProps.EndColor = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_ParticleProps.StartSize = 0.5f, 
	m_ParticleProps.SizeRandom = 0.3f,
	m_ParticleProps.EndSize = 0.0f;
	m_ParticleProps.LifeTime = 120;
	m_ParticleProps.Speed = { 0.0f, 0.0f };
	m_ParticleProps.SpeedRandom = { 0.2f };
	m_ParticleProps.Position = { 0.0f, 0.0f, 0.0f };
	m_ParticleProps.Rotation = 0.0f;
	m_ParticleProps.RotationRandom = 1.0f;
	m_ParticleProps.RotationSpeed = 0.1f;
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate()
{
	m_Camera.OnUpdate();
	m_ParticleSystem->OnUpdate();

	//Render
	Schmog::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Schmog::RenderCommand::Clear();

	//Schmog::Renderer2D::BeginScene(m_Camera.GetCamera());

	//float fac = 0.5f;
	//{
	//	for (int y = -10; y <= 10; y++)
	//	{
	//		for (int x = -10; x <= 10; x++)
	//		{
	//			Schmog::Renderer2DQuadProperties params{
	//				{m_Color1, 1.0f},
	//				0.0f,
	//				m_TilingFactor
	//			};

	//			Schmog::Renderer2D::DrawQuad({ fac * 1.1 * x, fac * 1.1 * y }, 
	//											{ fac, fac }, 
	//											m_Texture, 
	//											params
	//										);		
	//		}
	//	}
	//}

	//Schmog::Renderer2D::EndScene();

	if (Schmog::Input::IsMouseButtonPressed(Schmog::MouseCode::Button0))
	{
		auto mpos = Schmog::Input::GetMousePosition();
		int width = Schmog::Application::Get().GetWindow().GetWidth();
		int height = Schmog::Application::Get().GetWindow().GetHeight();

		int x = (mpos.x - width / 2) / width * m_Camera.GetZoomLevel() * 16.f/9.f * 2;
		int y = (height/2 - mpos.y) / height * m_Camera.GetZoomLevel() * 2;

		m_ParticleProps.Position = { x, y, 0.0f };
		m_ParticleSystem->Emit(m_ParticleProps, 5);
	}

	Schmog::Renderer2D::BeginScene(m_Camera.GetCamera());

	m_ParticleSystem->OnRender();

	Schmog::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_Color1));
	ImGui::SliderFloat("Tiling", &m_TilingFactor, 0.1f, 10.f);

	ImGui::Text("");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

bool Sandbox2D::OnMouseClicked(Schmog::MouseButtonPressedEvent& e)
{
	//if (e.GetMouseButton() == static_cast<uint32_t>(Schmog::MouseCode::ButtonLeft))
	//{
	//	m_ParticleSystem->Emit(m_ParticleProps, 5);
	//}

	return false;
}

void Sandbox2D::OnEvent(Schmog::Event& e)
{
	m_Camera.OnEvent(e);

	Schmog::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Schmog::MouseButtonPressedEvent>(SG_BIND_EVENT_FN(Sandbox2D::OnMouseClicked));
}
