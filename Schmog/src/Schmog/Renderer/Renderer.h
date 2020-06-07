#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "Schmog/Events/ApplicationEvent.h"

namespace Schmog {

	class Renderer 
	{
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* s_SceneData;

	};

}