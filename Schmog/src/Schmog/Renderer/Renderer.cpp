#include "sgpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Schmog {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->viewProjectionMatrix = camera.GetVP();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniform("u_ViewProjection", s_SceneData->viewProjectionMatrix);
		shader->SetUniform("u_Transform", transform);

		vertexArray->Bind(),
		RenderCommand::DrawIndexed(vertexArray);
	}

}