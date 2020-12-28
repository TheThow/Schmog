#pragma once

#include <glm/glm.hpp>
#include "Schmog/Game/Color.h"
#include "Schmog/Renderer/Texture.h"

namespace Schmog {

	struct SpriteRendererComponent
	{
		glm::vec2 TexCoords[4];
		RGBa Color = {};
		std::shared_ptr<Texture2D> Texture = nullptr;

		SpriteRendererComponent() = default;

		SpriteRendererComponent(RGBa color) {
			Color = color;
			Texture = nullptr;

			TexCoords[0] = glm::vec2(0.0f, 0.0f);
			TexCoords[1] = glm::vec2(1.0f, 0.0f);
			TexCoords[2] = glm::vec2(1.0f, 1.0f);
			TexCoords[3] = glm::vec2(0.0f, 1.0f);
		}
	};

}
