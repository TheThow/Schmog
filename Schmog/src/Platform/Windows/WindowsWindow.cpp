#include "sgpch.h"
#include "WindowsWindow.h"

#include "Schmog/Events/ApplicationEvent.h"
#include "Schmog/Events/MouseEvent.h"
#include "Schmog/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Schmog/Renderer/Renderer.h"

namespace Schmog {

	static uint8_t s_GLFWCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		SG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWCount == 0)
		{
			SG_CORE_INFO("GLFW Init");

			int success = glfwInit();
			SG_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

		}

		s_GLFWCount += 1;

#if defined(SG_DEBUG)
		if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = std::make_shared<OpenGLContext>(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData data = *(WindowData*) glfwGetWindowUserPointer(window);
				WindowResizeEvent windowEvent(width, height);
				data.eventCallback(windowEvent);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent windowEvent;
				data.eventCallback(windowEvent);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent keyPressedEvent(key, 0);
						data.eventCallback(keyPressedEvent);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent keyReleasedEvent(key);
						data.eventCallback(keyReleasedEvent);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent keyRepeatEvent(key, 1);
						data.eventCallback(keyRepeatEvent);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent keyTypedEvent(keycode, 0);
				data.eventCallback(keyTypedEvent);

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float) xOffset, (float) yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		s_GLFWCount -= 1;

		if (s_GLFWCount == 0)
		{
			SG_CORE_INFO("GLFW terminate");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


}