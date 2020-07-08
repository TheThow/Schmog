#pragma once

#include <glm/glm.hpp>

#include "Schmog/Renderer/Texture.h"

namespace Schmog {


	class SubTexture2D
	{
	public:
		SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		static std::shared_ptr<SubTexture2D> CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& gridSize, const glm::vec2& spriteSize = { 1, 1 });

		const std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];

	};


}



