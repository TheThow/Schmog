#pragma once

#include "Schmog/Renderer/Shader.h"
#include <glad/glad.h>

namespace Schmog {


	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetUniform(const std::string& name, const glm::vec4& vec) override;
		virtual void SetUniform(const std::string& name, const int value) override;
		virtual void SetUniform(const std::string& name, const float value) override;

		virtual void SetUniformArray(const std::string& name, const int* values, const uint32_t count) override;

		virtual int GetUniformLocation(const std::string& name);

		virtual void SetName(const std::string& name) override;
		virtual const std::string& GetName() const override { return m_Name; }


	private:
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string> shaderSources);
		std::string ReadFile(const std::string& filecontent);

	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
		std::string m_Name;
	};


}



