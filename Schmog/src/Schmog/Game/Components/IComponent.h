#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include "Schmog/Game/SerializerHelper.h"

namespace Schmog {

	struct IComponent
	{
		virtual ~IComponent() {}
		virtual void Serialize(YAML::Emitter& out) = 0;
		virtual void Deserialize(const YAML::Node& data) = 0;
	};

}