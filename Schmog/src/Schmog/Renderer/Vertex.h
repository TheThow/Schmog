#pragma once

#include <glm/glm.hpp>

namespace Schmog {

	struct QuadVertex
	{
		glm::vec3 Position;
		float TilingFactor;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

}