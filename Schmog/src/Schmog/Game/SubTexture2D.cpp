#include "sgpch.h"
#include "SubTexture2D.h"

namespace Schmog {


	SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = min;
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = max;
		m_TexCoords[3] = { min.x, max.y };
	}

	std::shared_ptr<SubTexture2D> SubTexture2D::CreateFromCoords(const std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& gridSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x / texture->GetWidth()) * gridSize.x, (coords.y / texture->GetHeight()) * gridSize.y };
		glm::vec2 max = { ((coords.x + spriteSize.x) / texture->GetWidth()) * gridSize.x, ((coords.y + spriteSize.y) / texture->GetHeight()) * gridSize.y };

		return std::make_shared<SubTexture2D>(texture, min, max);
	}


}