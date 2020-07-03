#include "sgpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include "ParticleSystem.h"
#include "Schmog/Core/Random.h"
#include "Schmog/Renderer/Renderer2D.h"


namespace Schmog {

	ParticleSystem::ParticleSystem()
	{
		m_ParticleDrawData.resize(1000000);
		m_ParticleProps.resize(1000000);
	}

	ParticleSystem::~ParticleSystem()
	{

	}

	void ParticleSystem::OnUpdate()
	{
		for (int i = 0; i < m_ParticleIndex; i++)
		{
			auto& props = m_ParticleProps[i];
			Particle& particle = m_ParticleDrawData[i];
			
			if (props.CurrentLifeTime <= 0)
			{
				props.Alive = false;
				SwapParticles(i);
				m_ParticleIndex--;
				i--;
				continue;
			}


			float lifeRatio = (float) props.CurrentLifeTime / (float) props.LifeTime;
			float size = glm::lerp(props.EndSize, props.StartSize, lifeRatio);
			glm::vec4 color = glm::lerp(props.EndColor, props.StartColor, lifeRatio);

			props.Position += glm::vec3(props.Speed, 0.0f);
			props.Rotation += props.RotationSpeed;
			props.Speed *= props.Damping;

			for (uint32_t vi = 0; vi < 4; vi++)
			{
				particle.vertices[vi].Translation.x = props.Position.x;
				particle.vertices[vi].Translation.y = props.Position.y;
				particle.vertices[vi].Rotation = props.Rotation;
				particle.vertices[vi].Color = color;
			}

			props.CurrentLifeTime -= 1;
		}

	}

	void ParticleSystem::OnRender()
	{
		Renderer2D::DrawParticles(m_ParticleDrawData, m_ParticleIndex);
	}


	void ParticleSystem::Emit(ParticleProperties& props, uint32_t count)
	{
		if (m_ParticleDrawData.size() < m_ParticleIndex + count)
		{
			m_ParticleDrawData.resize(m_ParticleDrawData.size() + 100000);
			m_ParticleProps.resize(m_ParticleDrawData.size() + 100000);
		}

		for (int i = 0; i < count; i++)
		{
			m_ParticleDrawData[m_ParticleIndex].vertices = {{
				{
					{ props.Position.x, props.Position.y },
					props.Position.z,
					props.Rotation,
					props.StartColor,
					{ props.StartSize, props.StartSize },
					{0.0f, 0.0f},
					0,
					1.0f
				},
				{
					{ props.Position.x, props.Position.y },
					props.Position.z,
					props.Rotation,
					props.StartColor,
					{ props.StartSize, props.StartSize },
					{1.0f, 0.0f},
					0,
					1.0f
				},
				{
					{ props.Position.x, props.Position.y },
					props.Position.z,
					props.Rotation,
					props.StartColor,
					{ props.StartSize, props.StartSize },
					{1.0f, 1.0f},
					0,
					1.0f
				},
				{
					{ props.Position.x, props.Position.y },
					props.Position.z,
					props.Rotation,
					props.StartColor,
					{ props.StartSize, props.StartSize },
					{0.0f, 1.0f},
					0,
					1.0f
				}
			}};

			m_ParticleProps[m_ParticleIndex] = { props };
			m_ParticleIndex++;
		}
	}

	void ParticleSystem::SwapParticles(uint32_t currentIndex)
	{
		std::swap(m_ParticleDrawData[currentIndex], m_ParticleDrawData[m_ParticleIndex - 1]);
		std::swap(m_ParticleProps[currentIndex], m_ParticleProps[m_ParticleIndex - 1]);
	}

}

