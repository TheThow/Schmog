#pragma once

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

#include "Schmog/Game/Color.h"

namespace Schmog {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec3& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec2& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const RGBa& v);

	namespace Convert {
		static glm::ivec3 YamlToIVec3(YAML::Node node)
		{
			if (!node.IsSequence() || node.size() != 3)
				SG_CORE_ASSERT(false, "Node not convertible to ivec3 " + node.Tag());
			return glm::ivec3(node[0].as<int>(), node[1].as<int>(), node[2].as<int>());
		}

		static glm::ivec2 YamlToIVec2(YAML::Node node)
		{
			if (!node.IsSequence() || node.size() != 2)
				SG_CORE_ASSERT(false, "Node not convertible to ivec2 " + node.Tag());
			return glm::ivec2(node[0].as<int>(), node[1].as<int>());
		}

		static RGBa YamlToIRGBa(YAML::Node node)
		{
			if (!node.IsSequence() || node.size() != 4)
				SG_CORE_ASSERT(false, "Node not convertible to rgba " + node.Tag());
			return RGBa((uint8_t) node[0].as<int>(), (uint8_t)node[1].as<int>(), (uint8_t)node[2].as<int>(), (uint8_t)node[3].as<int>());
		}
	}

}