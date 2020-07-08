#include "sgpch.h"
#include "FrameBuffer.h"
#include "Schmog/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"


namespace Schmog {


	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}