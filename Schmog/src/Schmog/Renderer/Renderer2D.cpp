#include "sgpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Schmog {

	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture2D> whiteTexture;
	};

	static std::unique_ptr<Renderer2DStorage> s_Data;

	void Renderer2D::Init()
	{
		s_Data.reset(new Renderer2DStorage());
		s_Data->vertexArray = VertexArray::Create();

		float vertices2[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f,  0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(vertices2, sizeof(vertices2));

		vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TexCoord"}
			});

		s_Data->vertexArray->AddVertexBuffer(vb);
		uint32_t indices2[6] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(indices2, 6);
		s_Data->vertexArray->SetIndexBuffer(ib);

		s_Data->shader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		s_Data.reset();
	}

	void Renderer2D::BeginScene(const OrthographicCamera camera)
	{
		s_Data->shader->Bind();
		s_Data->shader->SetUniform("u_ViewProjection", camera.GetVP());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(glm::vec3(position, 0), size, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(position, size, s_Data->whiteTexture, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color, float rotation)
	{
		DrawQuad(glm::vec3(position, 0), size, texture, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, const glm::vec4& color, float rotation)
	{
		texture->Bind(0);

		s_Data->shader->SetUniform("u_Color", color);
		s_Data->shader->SetUniform("u_Texture", 0);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size, 1.0f });
		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
		s_Data->shader->SetUniform("u_Transform", transform * rot);

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

}