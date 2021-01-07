#pragma once

#include <glm/glm.hpp>

#include "IComponent.h"

namespace Schmog {

	struct TransformComponent : public IComponent
	{
		glm::ivec3 Position = { 0, 0, 0 };
		glm::ivec2 Scale = { 1, 1 };
		int RotationDeg = 0;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;

		void Serialize(YAML::Emitter& out) override
		{
			out << YAML::Key << GetSerializationName();
			out << YAML::BeginMap;

			out << YAML::Key << "Position" << YAML::Value << Position;
			out << YAML::Key << "Scale" << YAML::Value << Scale;
			out << YAML::Key << "RotationDeg" << YAML::Value << RotationDeg;

			out << YAML::EndMap;
		}

		void Deserialize(const YAML::Node& data) override
		{
			Position = Convert::YamlToIVec3(data["Position"]);
			RotationDeg = data["RotationDeg"].as<int>();
			Scale = Convert::YamlToIVec2(data["Scale"]);
		}

		static std::string GetSerializationName()
		{
			return "TransformComponent";
		}
	};

}

