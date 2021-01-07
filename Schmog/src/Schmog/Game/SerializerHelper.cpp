#include "sgpch.h"
#include "SerializerHelper.h"

namespace Schmog {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const RGBa& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << (int)v.rgba[0] << (int)v.rgba[1] << (int)v.rgba[2] << (int)v.rgba[3] << YAML::EndSeq;
		return out;
	}

}