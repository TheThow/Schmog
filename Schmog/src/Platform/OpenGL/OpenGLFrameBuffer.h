#pragma once

#include "Schmog/Renderer/FrameBuffer.h"

namespace Schmog {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();

		virtual const FrameBufferSpec& GetSpecification() const override { return m_FrameBufferSpec; }
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };

		virtual void Invalidate() override;
		virtual void Resize(const uint32_t width, const uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpec m_FrameBufferSpec;
	};

}


