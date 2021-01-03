#pragma once

#include <glm/glm.hpp>

namespace Schmog {

	struct TransformComponent
	{
		glm::ivec3 Position = { 0, 0, 0 };
		glm::ivec2 Scale = { 1, 1 };
		int RotationDeg = 0;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
	};

}

