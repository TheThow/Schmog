#include "sgpch.h"
#include "Renderer.h"

namespace Schmog {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(const std::shared_ptr<OrthographicCamera> camera)
	{
		s_SceneData->ViewProjectionMatrix = camera->GetVP();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniform("u_Transform", transform);

		vertexArray->Bind(),
		RenderCommand::DrawIndexed(vertexArray);
	}

}