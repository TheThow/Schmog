#pragma once

#include <glm/glm.hpp>

namespace Schmog {

	struct QuadVertex
	{
		glm::vec3 Position;
		float TilingFactor;
		uint32_t Color;
		float TexIndex;
		glm::vec2 TexCoord;
	};

}