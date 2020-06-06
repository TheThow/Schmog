#include "sgpch.h"
#include "Shader.h"

#include "Schmog/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Schmog {

// ######################################
//	Shader
// ######################################

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, filepath);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SG_CORE_ASSERT(false, "RendererAPI:None not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		SG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}


// ######################################
//	Shader Library
// ######################################

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		SG_CORE_ASSERT(!Exists(name), "Shader identifier already exists: " + name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		shader->SetName(name);
		Add(shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SG_CORE_ASSERT(Exists(name), "Unknown shader identifier: " + name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}

