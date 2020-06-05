#pragma once

#include "Schmog/Renderer/Shader.h"
#include <glad/glad.h>

namespace Schmog {


	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetUniform(const std::string& name, const glm::vec4& vec) override;
		virtual void SetUniform(const std::string& name, const uint32_t value) override;
		virtual int GetUniformLocation(const std::string& name);

	private:
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string> shaderSources);
		std::string ReadFile(const std::string& filecontent);

	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};


}



