#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Schmog/Renderer/Vertex.h"
#include "Schmog/Core/Random.h"
#include "Color.h"

namespace Schmog {



	class ParticleSystem
	{
	public:

		struct ParticleProperties
		{
			RGBa StartColor = { 255, 255, 255, 255 };
			RGBa EndColor = { 255, 255, 255, 255 };

			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			float PositionRandom = 0.0f;

			glm::vec2 Speed = { 0.0f, 0.0f };
			float SpeedRandom = 0.0f;

			glm::vec2 Damping = { 0.0f, 0.0f };

			float Rotation = 0.0f;
			float RotationSpeed = 0.0f;
			float RotationRandom = 0.0f;

			float StartSize = 1.0f;
			float EndSize = 0.0f;
			float SizeRandom = 0.0f;

			uint32_t LifeTime = 120;
		};


		struct Particle
		{
			std::array<QuadVertex, 4> vertices;
		};



	public:

		ParticleSystem();
		~ParticleSystem();

		void OnUpdate();
		void OnRender();
		void Emit(ParticleProperties& props, uint32_t count = 1);

	private:
		void SwapParticles(uint32_t currentIndex);

	private:

		struct ParticleInternalProperties
		{
			RGBa StartColor = { 255, 255, 255, 255 };
			RGBa EndColor = { 255, 255, 255, 255 };

			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			glm::vec2 Speed = { 0.0f, 0.0f };
			glm::vec2 Damping = { 1.0f, 1.0f };

			float Rotation = 0.0f;
			float RotationSpeed = 0.0f;

			float StartSize = 1.0f;
			float EndSize = 0.0f;

			uint32_t LifeTime = 120;
			uint32_t CurrentLifeTime = LifeTime;
			
			bool Alive = false;

			ParticleInternalProperties()
			{

			}

			ParticleInternalProperties(ParticleProperties& props)
				: StartColor(props.StartColor), EndColor(props.EndColor), RotationSpeed(props.RotationSpeed),
				 EndSize(props.EndSize), Damping(props.Damping), LifeTime(props.LifeTime), CurrentLifeTime(props.LifeTime)
			{
				Position = props.Position + glm::vec3((Random::Float() - 0.5f) * props.PositionRandom, (Random::Float() - 0.5f) * props.PositionRandom, 0.0f);
				StartSize = props.StartSize + (Random::Float() - 0.5f) * props.SizeRandom;
				Speed = props.Speed + glm::vec2((Random::Float() - 0.5f) * props.SpeedRandom, (Random::Float() - 0.5f) * props.SpeedRandom);
				Rotation = props.Rotation + (Random::Float() - 0.5f) * props.RotationRandom;
				Alive = true;
			}
		};

		std::vector<Particle> m_ParticleDrawData;
		std::vector<ParticleInternalProperties> m_ParticleProps;

		uint32_t m_ParticleIndex = 0;
	};


}


