#pragma once

#include <GLFW/glfw3.h>

namespace Schmog {

	class Platform
	{
	public:
		static double GetTime() { return glfwGetTime(); }

	};


}