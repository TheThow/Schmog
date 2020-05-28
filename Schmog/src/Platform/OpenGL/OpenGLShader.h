#pragma once

#include "Schmog/Renderer/Shader.h"

namespace Schmog {



	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc),
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID = 0;
	};


}



