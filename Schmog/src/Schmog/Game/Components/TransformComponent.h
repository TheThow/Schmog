#pragma once

#include <glm/glm.hpp>

namespace Schmog {

	struct TransformComponent
	{
		TransformComponent() = default;

		glm::vec3 Position = { 0, 0, 0 };
		glm::vec2 Scale = { 1.0, 1.0 };
		float Rotation = 0;
	};

}

