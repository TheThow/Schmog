#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Schmog {

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform(const std::string& name, glm::mat4& matrix) = 0;
		virtual int GetUniformLocation(const std::string& name) = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	};

}