#pragma once

#include <memory>

#include "Schmog.h"


class Sandbox2D : public Schmog::Layer
{

public:
	Sandbox2D()
		: Layer("Sandbox 2D"), m_Camera(16.f/9.f)
	{

	}
	~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(Schmog::Event& e) override;

private:
	Schmog::OrthographicCameraController m_Camera;


	// Temp
	std::shared_ptr<Schmog::Shader> m_Shader;

	glm::vec3 m_Color1 = { 0.8f, 0.2f, 0.8f };
	std::shared_ptr<Schmog::VertexArray> m_VA;

};

