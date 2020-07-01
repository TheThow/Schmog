#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Schmog/Core/Random.h"

namespace Schmog {



	class ParticleSystem
	{
	public:

		struct ParticleProperties
		{
			glm::vec4 StartColor = { 1.0f, 1.0f, 1.0f, 1.0f };
			glm::vec4 EndColor = { 1.0f, 1.0f, 1.0f, 0.0f };

			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			float PositionRandom = 0.0f;

			glm::vec2 Speed = { 0.0f, 0.0f };
			float SpeedRandom = 0.0f;

			float Rotation = 0.0f;
			float RotationSpeed = 0.0f;
			float RotationRandom = 0.0f;

			float StartSize = 1.0f;
			float EndSize = 0.0f;
			float SizeRandom = 0.0f;

			uint32_t LifeTime = 120;
		};


		struct Vertex
		{
			glm::vec3 Position = { 0.0f, 0.0f, 0.0f};
			glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			glm::vec2 TexCoord = { 0.0f, 0.0f };
			float TexIndex = 0;
			float TilingFactor = 1.0f;
		};

		struct Particle
		{
			std::array<Vertex, 4> vertices;
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
			glm::vec4 StartColor = { 1.0f, 1.0f, 1.0f, 1.0f };
			glm::vec4 EndColor = { 1.0f, 1.0f, 1.0f, 0.0f };

			glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
			glm::vec2 Speed = { 0.0f, 0.0f };

			float Rotation = 0.0f;
			float RotationSpeed = 0.0f;

			float StartSize = 1.0f;
			float EndSize = 0.0f;

			uint32_t LifeTime = 120;
			uint32_t CurrentLifeTime = LifeTime;
			
			bool Alive = false;

			ParticleInternalProperties()
				: StartColor({ 1.0f, 1.0f, 1.0f, 1.0f }), EndColor({ 0.0f, 0.0f, 0.0f, 0.0f }), Position({ 0.0f, 0.0f, 0.0f }),
				RotationSpeed(0.0f), EndSize(0.0f), LifeTime(120), CurrentLifeTime(LifeTime),
				StartSize(1.0f), Speed(0.0f), Rotation(0.0f)
			{

			}

			ParticleInternalProperties(ParticleProperties& props)
				: StartColor(props.StartColor), EndColor(props.EndColor),
				RotationSpeed(props.RotationSpeed) , EndSize(props.EndSize), LifeTime(props.LifeTime), CurrentLifeTime(props.LifeTime)
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


