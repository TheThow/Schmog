#pragma once

#include "Camera.h"
#include "Texture.h"
#include "Schmog/Game/ParticleSystem.h"

namespace Schmog {


	struct Renderer2DQuadProperties
	{
		const glm::vec4 Color = glm::vec4(1.0f);
		float Rotation = 0.0f;
		float TilingFactor = 1.0f;
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

		static void DrawParticles(std::vector<ParticleSystem::Particle>& particles, uint32_t maxIndex);

		// Stats
		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;
		};
		static void ResetStats();
		static Statistics GetStats();

	private:
		static void ResetData();
	};



}


