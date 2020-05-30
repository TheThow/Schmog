#pragma once

#include "Schmog/Renderer/GraphicsContext.h"



struct GLFWwindow;

namespace Schmog {


	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
		void SetViewPort(int width, int height) override;

	private:
		GLFWwindow* m_windowHandle;

	};

}



