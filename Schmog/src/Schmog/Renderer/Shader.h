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

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniform(const std::string& name, const glm::vec4& vec) = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	};

}