#include "Sandbox2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

#include <iostream>


static const uint32_t s_MapWidth = 24;
static const uint32_t s_MapHeight = 14;
static const char* s_MapTiles = 
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwgggggggwwwwwwwww"
"wwwwwwwgggggggggwwwwwwww"
"wwwwwwggggggggwwwwwwwwww"
"wwwwwwgggggggggwwwwwwwww"
"wwwwwwwgggggggggwwwwwwww"
"wwwwwwwwgggggggwwwwwwwww"
"wwwwwwwwwgggggwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwww"
;


void Sandbox2D::OnAttach()
{
	m_SpriteTexture = Schmog::Texture2D::Create("assets/textures/RPGpack_sheet.png");
	m_Texture = Schmog::Texture2D::Create("assets/textures/Checkerboard.png");

	m_TextureMap['g'] = Schmog::SubTexture2D::CreateFromCoords(m_SpriteTexture, { 1, 11 }, { 64, 64 });
	m_TextureMap['w'] = Schmog::SubTexture2D::CreateFromCoords(m_SpriteTexture, { 11, 11 }, { 64, 64 });

	m_ParticleProps.StartColor = { 254, 212, 123, 255 };
	m_ParticleProps.EndColor = { 254, 109, 41, 255 };
	m_ParticleProps.StartSize = 0.5f, 
	m_ParticleProps.SizeRandom = 0.3f,
	m_ParticleProps.EndSize = 0.0f;
	m_ParticleProps.LifeTime = 120*4;
	m_ParticleProps.Speed = { 0.0f, 0.0f };
	m_ParticleProps.SpeedRandom = { 0.4f };
	m_ParticleProps.Position = { 0.0f, 0.0f, 0.0f };
	m_ParticleProps.PositionRandom = 0.1f;
	m_ParticleProps.Rotation = 0.0f;
	m_ParticleProps.RotationRandom = 1.0f;
	m_ParticleProps.RotationSpeed = 0.1f;
	m_ParticleProps.Damping = { 0.95f, 0.95f };

	m_Camera.SetZoomLevel(10.0f);

	Schmog::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

	Schmog::FrameBufferSpec fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	std::shared_ptr<Schmog::Scene> scene = std::make_shared<Schmog::Scene>();
	Schmog::Entity entity = scene->CreateEntity();
	std::cout << "HAS COMPONENT " << entity.HasComponent<Schmog::TransformComponent>() << std::endl;

	auto& trans = scene->GetComponents<Schmog::TransformComponent>();
	Schmog::Entity entity2 = scene->CreateEntity();

	auto cam = scene->CreateEntity();
	cam.AddComponent(Schmog::CameraComponent());
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate()
{

	Schmog::Renderer2D::ResetStats();
	m_Camera.OnUpdate();

	//Render
	Schmog::RenderCommand::Clear();

	Schmog::Renderer2D::BeginScene(m_Camera.GetCamera().GetVP());

	Schmog::Renderer2DQuadProperties params {
		{255,255,255,255},
		0.0f,
		1.0f
	};


	float fac = 1.f;
	{
		for (int y = 5; y <= 6; y++)
		{
			for (int x = 7; x <= 8; x++)
			{

				Schmog::Renderer2D::DrawQuad({ fac * 1.1 * x - 7, fac * 1.1 * y - 5 },
					{ fac, fac },
					Schmog::SubTexture2D::CreateFromCoords(m_SpriteTexture, { x, y }, { 64, 64 }),
					params
				);
			}
		}
	}


	fac = 1.f;
	{
		for (uint32_t y = 0; y < s_MapHeight; y++)
		{
			for (uint32_t x = 0; x < s_MapWidth; x++)
			{
				char tile = s_MapTiles[x + y * s_MapWidth];

				Schmog::Renderer2D::DrawQuad({ fac * x - 7, fac * y - 5 }, 
												{ fac, fac }, 
												m_TextureMap[tile],
												params
											);		
			}
		}
	}

	Schmog::Renderer2D::DrawQuad({ 0, 0 },
		{ 10, 10 },
		m_Texture,
		params
	);

	Schmog::Renderer2D::EndScene();

	if (Schmog::Input::IsMouseButtonPressed(Schmog::MouseButtonCode::Button0))
	{
		auto mpos = Schmog::Input::GetMousePosition();
		float width = (float) Schmog::Application::Get().GetWindow().GetWidth();
		float height = (float) Schmog::Application::Get().GetWindow().GetHeight();

		float x = ((float)mpos.x - width / 2.f) / width * m_Camera.GetZoomLevel() * m_Camera.GetAspectRatio() * 2.f + m_Camera.GetCamera().GetPosition().x;
		float y = (height/2.f - (float)mpos.y) / height * m_Camera.GetZoomLevel() * 2.f + m_Camera.GetCamera().GetPosition().y;

		m_ParticleProps.Position = { x, y, 0.0f };
		m_ParticleSystem->Emit(m_ParticleProps, 50);
	}

	Schmog::Renderer2D::BeginScene(m_Camera.GetCamera().GetVP());

	m_ParticleSystem->OnRender();

	Schmog::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_Color1));

	ImGui::Text("");

	auto stats = Schmog::Renderer2D::GetStats();

	ImGui::Text("Draw Calls: %i", stats.drawCalls); 
	ImGui::Text("Quad: %i", stats.quadCount);

	ImGui::Text("");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

bool Sandbox2D::OnMouseClicked(Schmog::MouseButtonPressedEvent& e)
{
//	if (e.GetMouseButton() == Schmog::MouseButtonCode::ButtonLeft)
//	{
//		m_ParticleSystem->Emit(m_ParticleProps, 100);
//	}
//
	if (e.GetMouseButton() == Schmog::MouseButtonCode::ButtonRight)
	{
		m_ParticleSystem->Emit(m_ParticleProps, 1000);
	}
//
	return false;
}

void Sandbox2D::OnEvent(Schmog::Event& e)
{
	m_Camera.OnEvent(e);

	Schmog::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Schmog::MouseButtonPressedEvent>(SG_BIND_EVENT_FN(Sandbox2D::OnMouseClicked));
}
