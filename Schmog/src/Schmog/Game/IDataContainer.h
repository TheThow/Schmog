#pragma once
#include <cstdint>

namespace Schmog {

	class IDataContainer
	{
	public:
		virtual void Remove(uint32_t id) = 0;
	};

}