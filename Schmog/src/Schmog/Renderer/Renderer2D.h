#pragma once

#include "Camera.h"
#include "Texture.h"

namespace Schmog {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f), float rotation = 0.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f), float rotation = 0.0f);
	};

	struct Renderer2DQuadParameters 
	{
		const glm::vec4 color;
		float rotation;
	};


}


