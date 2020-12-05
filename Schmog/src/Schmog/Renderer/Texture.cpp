#include "sgpch.h"
#include "Texture.h"

#include "Schmog/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Schmog {


	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}