#include "sgpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Schmog {


	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		SG_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SG_CORE_ASSERT(status, "Failed to initialize glad!");

		SG_CORE_INFO("-- OpenGL Info --");
		SG_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		SG_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		SG_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}