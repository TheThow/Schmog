#pragma once

#include "Schmog/Renderer/RendererAPI.h"

namespace Schmog {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void SetVP(glm::mat4 vp) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};
}



