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

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpec m_FrameBufferSpec;
	};

}


