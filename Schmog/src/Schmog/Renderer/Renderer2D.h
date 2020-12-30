#pragma once

#include "Camera.h"
#include "Texture.h"
#include "Vertex.h"
#include "Schmog/Game/ParticleSystem.h"
#include "Schmog/Game/Color.h"
#include "Schmog/Game/SubTexture2D.h"
#include <Schmog\Renderer\OrthographicCamera.h>

#include "Schmog/Game/Components/TransformComponent.h"
#include "Schmog/Game/Components/SpriteRendererComponent.h"


namespace Schmog {

	struct Renderer2DQuadProperties
	{
		RGBa Color = { 255, 255, 255, 255 };
		float Rotation = 0.0f;
		float TilingFactor = 1.0f;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const glm::mat4& projection);
		static void BeginScene(const glm::mat4& projection, const TransformComponent& transformComponent);
		static void EndScene();

		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Renderer2DQuadProperties& parameters);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Renderer2DQuadProperties& parameters);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const Renderer2DQuadProperties& parameters);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const Renderer2DQuadProperties& parameters);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subtexture, const Renderer2DQuadProperties& parameters);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subtexture, const Renderer2DQuadProperties& parameters);

		static void Renderer2D::DrawQuad(const TransformComponent& transform, const SpriteRendererComponent& spriteComponent);

		static void DrawParticles(std::vector<ParticleSystem::Particle>& particles, uint32_t maxIndex);

		


		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static void ResetData();
		static void AddQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec2* texCoords, const Renderer2DQuadProperties& parameters);
	};



}


