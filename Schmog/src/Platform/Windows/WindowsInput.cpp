#include "sgpch.h"
#include "WindowsInput.h"
#include "Schmog/Application.h"

#include <GLFW/glfw3.h>

namespace Schmog {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

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