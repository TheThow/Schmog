#pragma once

#include <array>

#include <glm/glm.hpp>

#include "Schmog/Game/Color.h"
#include "Schmog/Renderer/Texture.h"
#include "IComponent.h"

namespace Schmog {

	struct SpriteRendererComponent : public IComponent
	{
		std::array<glm::vec2, 4> TexCoords;
		RGBa Color = {};
		std::shared_ptr<Texture2D> Texture = nullptr;

		SpriteRendererComponent() 
		{
			Color = RGBa(255, 255, 255, 255);
			Texture = nullptr;

			TexCoords[0] = glm::vec2(0.0f, 0.0f);
			TexCoords[1] = glm::vec2(1.0f, 0.0f);
			TexCoords[2] = glm::vec2(1.0f, 1.0f);
			TexCoords[3] = glm::vec2(0.0f, 1.0f);
		}

		SpriteRendererComponent(RGBa color) {
			Color = color;
			Texture = nullptr;

			TexCoords[0] = glm::vec2(0.0f, 0.0f);
			TexCoords[1] = glm::vec2(1.0f, 0.0f);
			TexCoords[2] = glm::vec2(1.0f, 1.0f);
			TexCoords[3] = glm::vec2(0.0f, 1.0f);
		}

		void Serialize(YAML::Emitter& out) override
		{
			out << YAML::Key << GetSerializationName();
			out << YAML::BeginMap;

			out << YAML::Key << "Color" << YAML::Value << Color;

			out << YAML::EndMap;
		}

		void Deserialize(const YAML::Node& data) override
		{
			Color = Convert::YamlToIRGBa(data["Color"]);
		}

		static std::string GetSerializationName()
		{
			return "SpriteRendererComponent";
		}
	};

}
