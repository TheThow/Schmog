#pragma once

#include <glm/glm.hpp>
#include "Schmog/Game/Color.h"

namespace Schmog {

	struct SpriteRendererComponent
	{
		SpriteRendererComponent() = default;

		glm::vec2 TexCoord = { 0, 0 };
		RGBa Color = {};
		uint32_t TexIndex = 0;
	};

}

