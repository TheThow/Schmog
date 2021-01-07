#pragma once
#include <cstdint>
#include <yaml-cpp/yaml.h>

namespace Schmog {

	class IDataContainer
	{
	public:
		virtual ~IDataContainer() {}
		virtual bool ContainsEntity(uint32_t id) = 0;
		virtual void Remove(uint32_t id) = 0;
	};

}