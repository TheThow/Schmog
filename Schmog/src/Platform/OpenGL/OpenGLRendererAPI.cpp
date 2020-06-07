#include "sgpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>


namespace Schmog {

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         SG_CORE_CRITICAL("OpenGL: {0}", message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       SG_CORE_ERROR("OpenGL: {0}", message); return;
		case GL_DEBUG_SEVERITY_LOW:          SG_CORE_WARN("OpenGL: {0}", message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: SG_CORE_TRACE("OpenGL: {0}", message); return;
		}

		SG_CORE_ASSERT(false, "Unknown severity level!");
	}


	void OpenGLRendererAPI::Init()
	{
#ifdef SG_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetVP(glm::mat4 vp)
	{
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}