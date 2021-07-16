#pragma once

#include "Schmog/Renderer/FrameBuffer.h"

namespace Schmog {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();

		virtual const FrameBufferSpec& GetSpecification() const override { return m_FrameBufferSpec; }
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { return m_ColorAttachments.at(index); };

		virtual void Invalidate() override;
		virtual void Resize(const uint32_t width, const uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t m_RendererID = 0;
		FrameBufferSpec m_FrameBufferSpec;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
		FrameBufferTextureSpecification m_DepthAttachmentSpec = FrameBufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};

}


