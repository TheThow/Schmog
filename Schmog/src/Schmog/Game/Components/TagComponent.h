#pragma once
#include <string>

#include "IComponent.h"

namespace Schmog {

	struct TagComponent : public IComponent
	{
		std::string Tag;

		TagComponent()
		{
			Tag = "Entity";
		}

		TagComponent(std::string name)
			: Tag(name) {}

		void Serialize(YAML::Emitter& out) override
		{
			out << YAML::Key << GetSerializationName();
			out << YAML::BeginMap;

			out << YAML::Key << "Tag" << YAML::Value << Tag;

			out << YAML::EndMap; 
		}

		void Deserialize(const YAML::Node& data) override
		{
			Tag = data["Tag"].as<std::string>();
		}

		static std::string GetSerializationName()
		{
			return "TagComponent";
		}
	};
}