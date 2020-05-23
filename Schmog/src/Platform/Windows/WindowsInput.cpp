#include "sgpch.h"
#include "WindowsInput.h"
#include "Schmog/Application.h"

#include <GLFW/glfw3.h>

namespace Schmog {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	Input::MousePosition WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}



}