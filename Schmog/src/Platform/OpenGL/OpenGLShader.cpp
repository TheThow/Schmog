#include "sgpch.h"
#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.inl>

#include <fstream>
#include <filesystem>

namespace Schmog {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		SG_CORE_ASSERT(false, "Unknown shader type: " + type);
		return 0;
	}


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
		SetName(name);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto sources = Preprocess(source);
		Compile(sources);
		SetName(name);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto sources = Preprocess(source);
		Compile(sources);

		//assets/shaders/Texture.glsl -> Texture
		std::filesystem::path path = filepath;
		SetName(path.stem().string());
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		auto loc = GetUniformLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& vec)
	{
		auto loc = GetUniformLocation(name);
		glUniform4f(loc, vec[0], vec[1], vec[2], vec[3]);
	}

	void OpenGLShader::SetUniform(const std::string& name, const int value)
	{
		auto loc = GetUniformLocation(name);
		glUniform1i(loc, value);
	}

	void OpenGLShader::SetUniform(const std::string& name, const float value)
	{
		auto loc = GetUniformLocation(name);
		glUniform1f(loc, value);
	}


	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		{
			return m_UniformLocationCache[name];
		}
		auto loc = glGetUniformLocation(m_RendererID, name.c_str());
		m_UniformLocationCache[name] = loc;
		return loc;
	}

	void OpenGLShader::SetName(const std::string& name)
	{
		m_Name = name;
		glObjectLabel(GL_PROGRAM, m_RendererID, -1, name.c_str());
	}


	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			SG_CORE_ASSERT(eol != std::string::npos, "Shader Source: Syntax Error");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> shaderSources)
	{
		GLuint program = glCreateProgram();
		m_RendererID = program;
		//std::vector<GLint> shaderIds;
		//shaderIds.reserve(shaderSources.size());
		SG_CORE_ASSERT(shaderSources.size() <= 4, "Max 4 shaders supported at one time");
		std::array<GLint, 4> shaderIds;
		unsigned short shaderIdCounter = 0;


		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				SG_CORE_ERROR("Vertex Shader compilation failure: {0}", infoLog.data());
				SG_CORE_ASSERT(false, "Shader compilation failure");

				return;
			}

			glAttachShader(program, shader);
			shaderIds[shaderIdCounter] = shader;
			shaderIdCounter++;
		}


		glLinkProgram(program);


		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);


			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (unsigned short i = 0; i < shaderIdCounter; i++)
			{
				glDeleteShader(shaderIds[i]);
			}


			SG_CORE_ERROR("Shader linking failure: {0}", infoLog.data());
			SG_CORE_ASSERT(false, "Shader linking failure");

			return;
		}

		for (unsigned short i = 0; i < shaderIdCounter; i++)
		{
			glDetachShader(program, shaderIds[i]);
			glDeleteShader(shaderIds[i]);
		}
		
		m_RendererID = program;
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		SG_CORE_ASSERT(in, "File not found: " + filepath);

		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();

		return result;
	}

}