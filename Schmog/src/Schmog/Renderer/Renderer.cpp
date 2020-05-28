#include "sgpch.h"
#include "Renderer.h"

namespace Schmog {

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind(),
		RenderCommand::DrawIndexed(vertexArray);
	}

}