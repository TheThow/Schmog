#pragma once

#include "Schmog/Core/Core.h"


namespace Schmog {

	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};


	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpec& spec);

		virtual const FrameBufferSpec& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual void Invalidate() = 0;
		virtual void Resize(const uint32_t width, const uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

}