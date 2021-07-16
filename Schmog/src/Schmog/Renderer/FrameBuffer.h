#pragma once

#include "Schmog/Core/Core.h"


namespace Schmog {

	enum class FrameBufferTextureFormat 
	{
		None = 0,

		RGBA8,

		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;

		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			: TextureFormat(format) {}

		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
	};

	struct FrameBufferAttachmentSpecification
	{
		FrameBufferAttachmentSpecification() = default;

		FrameBufferAttachmentSpecification(const std::initializer_list<FrameBufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FrameBufferTextureSpecification> Attachments;
	};

	struct FrameBufferSpec
	{
		FrameBufferAttachmentSpecification Attachments;

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
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual void Invalidate() = 0;
		virtual void Resize(const uint32_t width, const uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

}