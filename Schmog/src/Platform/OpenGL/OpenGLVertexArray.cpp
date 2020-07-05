#include "sgpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Schmog
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Schmog::ShaderDataType::Float:    return GL_FLOAT;
			case Schmog::ShaderDataType::Float2:   return GL_FLOAT;
			case Schmog::ShaderDataType::Float3:   return GL_FLOAT;
			case Schmog::ShaderDataType::Float4:   return GL_FLOAT;
			case Schmog::ShaderDataType::Mat3:     return GL_FLOAT;
			case Schmog::ShaderDataType::Mat4:     return GL_FLOAT;
			case Schmog::ShaderDataType::Int:      return GL_INT;
			case Schmog::ShaderDataType::Int2:     return GL_INT;
			case Schmog::ShaderDataType::Int3:     return GL_INT;
			case Schmog::ShaderDataType::Int4:     return GL_INT;
			case Schmog::ShaderDataType::Bool:     return GL_BOOL;
			case Schmog::ShaderDataType::UInt:     return GL_UNSIGNED_INT;
			case Schmog::ShaderDataType::UByte:    return GL_UNSIGNED_BYTE;
			case Schmog::ShaderDataType::UByte4:   return GL_UNSIGNED_BYTE;
		}

		SG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		Bind();
		vertexBuffer->Bind();

		SG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "No vertex buffer layout specified");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			if ((element.type == Schmog::ShaderDataType::UInt 
				|| element.type == Schmog::ShaderDataType::Int
				|| element.type == Schmog::ShaderDataType::Int2
				|| element.type == Schmog::ShaderDataType::Int3
				|| element.type == Schmog::ShaderDataType::Int4
				|| element.type == Schmog::ShaderDataType::UByte
				|| element.type == Schmog::ShaderDataType::UByte4)
				&& element.normalized == false)
			{
				glVertexAttribIPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					layout.GetStride(),
					(const void*)element.offset);
			}
			else
			{
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
			}
			index++;

		}

		m_VertexBuffers.push_back(vertexBuffer);
		Unbind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
		Unbind();
	}


}


