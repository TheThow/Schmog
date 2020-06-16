#pragma once

#include "Camera.h"
#include "Texture.h"

namespace Schmog {


	struct Renderer2DQuadProperties
	{
		const glm::vec4 color = glm::vec4(1.0f);
		float rotation = 0.0f;
		float tilingFactor = 1.0f;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera camera);
		static void EndScene();

		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Renderer2DQuadProperties& parameters);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Renderer2DQuadProperties& parameters);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, Renderer2DQuadProperties& parameters);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, Renderer2DQuadProperties& parameters);

	private:
		static void ResetData();
	};



}


