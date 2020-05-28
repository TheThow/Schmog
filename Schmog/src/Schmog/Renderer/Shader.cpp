#include "sgpch.h"
#include "Shader.h"

#include "Schmog/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Schmog {



	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

