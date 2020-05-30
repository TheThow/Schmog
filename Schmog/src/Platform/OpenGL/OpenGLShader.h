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

		virtual void SetUniform(const std::string& name, glm::mat4& matrix) override;
		virtual int GetUniformLocation(const std::string& name) override;

	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};


}



