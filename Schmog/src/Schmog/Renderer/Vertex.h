#pragma once

#include <glm/glm.hpp>
#include "Schmog/Game/Color.h"

namespace Schmog {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		RGBa Color;
		uint32_t TexIndex;
	};

}