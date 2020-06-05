#pragma once

#include <memory>

#include "RendererAPI.h"


namespace Schmog {

	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}




	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;


	};

}

