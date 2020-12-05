#include "sgpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Platform/Platform.h"


namespace Schmog {



	struct Renderer2DData
	{
		static const uint32_t MAX_QUADS = 10000;
		static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		static const uint32_t MAX_INDICES = MAX_QUADS * 6;
		static const uint32_t MAX_TEXTURE_SLOTS = 32; // TODO

		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> textureSlots;
		uint32_t textureSlotIndex = 1; // 0 = white

		glm::vec4 quadVertexPositions[4];
		glm::vec2 quadTextureCoords[4];

		Renderer2D::Statistics stats;
	};

	static Renderer2DData s_Data;



	void Renderer2D::Init()
	{
		s_Data.vertexArray = VertexArray::Create();

		BufferLayout vbLayout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::UByte4, "a_Color", true},
			{ ShaderDataType::UInt, "a_TexIndex"}
		};

		s_Data.vertexBuffer = VertexBuffer::Create(s_Data.MAX_VERTICES * sizeof(QuadVertex));
		s_Data.vertexBuffer->SetLayout(vbLayout);
		s_Data.vertexArray->AddVertexBuffer(s_Data.vertexBuffer);

		s_Data.quadVertexBufferBase = new QuadVertex[s_Data.MAX_VERTICES];


		uint32_t* quadIndices = new uint32_t[s_Data.MAX_INDICES];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MAX_INDICES; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}


		std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(quadIndices, s_Data.MAX_INDICES);
		s_Data.vertexArray->SetIndexBuffer(ib);
		delete[] quadIndices;

		s_Data.shader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data.whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int samplers[s_Data.MAX_TEXTURE_SLOTS];
		for (uint32_t i = 0; i < s_Data.MAX_TEXTURE_SLOTS; i++)
			samplers[i] = i;


		s_Data.shader->Bind();
		s_Data.shader->SetUniformArray("u_Texture", samplers, s_Data.MAX_TEXTURE_SLOTS);

		s_Data.textureSlots[0] = s_Data.whiteTexture;

		s_Data.quadVertexPositions[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		s_Data.quadVertexPositions[1] = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		s_Data.quadVertexPositions[2] = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		s_Data.quadVertexPositions[3] = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);

		s_Data.quadTextureCoords[0] = glm::vec2(0.0f, 0.0f);
		s_Data.quadTextureCoords[1] = glm::vec2(1.0f, 0.0f);
		s_Data.quadTextureCoords[2] = glm::vec2(1.0f, 1.0f);
		s_Data.quadTextureCoords[3] = glm::vec2(0.0f, 1.0f);
	}

	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(const glm::mat4 projection)
	{
		s_Data.shader->Bind();
		s_Data.shader->SetUniform("u_ViewProjection", projection);

		ResetData();
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*) s_Data.quadVertexBufferPtr - (uint8_t*) s_Data.quadVertexBufferBase;

		if (dataSize == 0)
		{
			return;
		}

		s_Data.vertexBuffer->SetData(s_Data.quadVertexBufferBase, dataSize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.textureSlotIndex; i++)
		{
			s_Data.textureSlots[i]->Bind(i);
		}

		s_Data.vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray, s_Data.quadIndexCount);
		s_Data.stats.drawCalls += 1;
	}

	void Renderer2D::ResetStats()
	{
		s_Data.stats.drawCalls = 0;
		s_Data.stats.quadCount = 0;
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.stats;
	}

	void Renderer2D::ResetData()
	{
		s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;
		s_Data.quadIndexCount = 0;

		s_Data.textureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Renderer2DQuadProperties& parameters)
	{
		DrawQuad(glm::vec3(position, 0), size, parameters);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Renderer2DQuadProperties& parameters)
	{
		DrawQuad(position, size, s_Data.whiteTexture, parameters);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const Renderer2DQuadProperties& parameters)
	{
		DrawQuad(glm::vec3(position, 0), size, texture, parameters);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const Renderer2DQuadProperties& parameters)
	{
		AddQuad(position, size, texture, s_Data.quadTextureCoords, parameters);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subtexture, const Renderer2DQuadProperties& parameters)
	{
		DrawQuad(glm::vec3(position, 0), size, subtexture, parameters);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture2D> subtexture, const Renderer2DQuadProperties& parameters)
	{
		AddQuad(position, size, subtexture->GetTexture(), subtexture->GetTexCoords(), parameters);
	}

	void Renderer2D::DrawQuad(const TransformComponent& transform, const SpriteRendererComponent& spriteComponent)
	{
		AddQuad(transform.Position, transform.Scale, spriteComponent.Texture, s_Data.quadTextureCoords, {});
	}

	void Renderer2D::AddQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec2* texCoords, const Renderer2DQuadProperties& parameters)
	{
		if (s_Data.quadIndexCount >= s_Data.MAX_INDICES)
		{
			EndScene();
			ResetData();
		}

		int textureIndex = -1;

		for (uint32_t i = 0; i < s_Data.textureSlotIndex; i++)
		{
			if (*s_Data.textureSlots[i].get() == *texture.get())
				textureIndex = i;
		}

		if (textureIndex == -1)
		{
			textureIndex = s_Data.textureSlotIndex;
			s_Data.textureSlots[s_Data.textureSlotIndex] = texture;
			s_Data.textureSlotIndex += 1;
		}


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size, 1.0f });

		//Rotation is expensive
		if (parameters.Rotation) {
			auto rot = glm::rotate(glm::mat4(1.0f), parameters.Rotation, glm::vec3(0, 0, 1));
			transform *= rot;
		}

		for (int vi = 0; vi < 4; vi++)
		{
			s_Data.quadVertexBufferPtr->Position = transform * s_Data.quadVertexPositions[vi];
			s_Data.quadVertexBufferPtr->Color = parameters.Color;
			s_Data.quadVertexBufferPtr->TexCoord = texCoords[vi];
			s_Data.quadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.quadVertexBufferPtr++;
		}

		s_Data.quadIndexCount += 6;
		s_Data.stats.quadCount += 1;
	}

	void Renderer2D::DrawParticles(std::vector<ParticleSystem::Particle>& particles, uint32_t maxIndex)
	{
		for (uint32_t i = 0; i < maxIndex; i += Renderer2DData::MAX_QUADS)
		{
			uint32_t count = std::min(maxIndex - i, Renderer2DData::MAX_QUADS);

			uint8_t* start = (uint8_t*) &particles[i];
			uint8_t* end = (uint8_t*) &particles[i + count];

			uint32_t dataSize = end - start;
			s_Data.vertexBuffer->SetData(start, dataSize);
			s_Data.quadIndexCount = count*6;
			Flush();

			s_Data.stats.quadCount += count;
		}
	}


}