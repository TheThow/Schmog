#include "sgpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include "ParticleSystem.h"
#include "Schmog/Core/Random.h"
#include "Schmog/Renderer/Renderer2D.h"


namespace Schmog {

	struct VertexPositions
	{
		glm::vec4 BottomLeft = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		glm::vec4 BottomRight = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		glm::vec4 TopRight = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		glm::vec4 TopLeft = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	} vertexPositions;



	ParticleSystem::ParticleSystem()
	{
		m_ParticleDrawData.resize(1000000, {});
		m_ParticleProps.resize(1000000, {});
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

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), props.Position)
				* glm::rotate(glm::mat4(1.0f), props.Rotation, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), { size, size, 1.0f });

			glm::vec4* vertexPositionPointer = &vertexPositions.BottomLeft;
			

			for (uint32_t vi = 0; vi < 4; vi++)
			{
				particle.vertices[vi].Position = transform * vertexPositionPointer[vi];
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
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), props.Position)
			* glm::scale(glm::mat4(1.0f), { props.StartSize, props.StartSize, 1.0f });


		if (m_ParticleDrawData.size() < m_ParticleIndex)
		{
			m_ParticleDrawData.resize(m_ParticleDrawData.size() + 100000);
			m_ParticleProps.resize(m_ParticleDrawData.size() + 100000);
		}

		for (int i = 0; i < count; i++)
		{
			m_ParticleDrawData[m_ParticleIndex].vertices = {{
				{
					transform * vertexPositions.BottomLeft,
					props.StartColor,
					{0.0f, 0.0f},
					0,
					1.0f
				},
				{
					transform * vertexPositions.BottomRight,
					props.StartColor,
					{1.0f, 0.0f},
					0,
					1.0f
				},
				{
					transform * vertexPositions.TopRight,
					props.StartColor,
					{1.0f, 1.0f},
					0,
					1.0f
				},
				{
					transform * vertexPositions.TopLeft,
					props.StartColor,
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

