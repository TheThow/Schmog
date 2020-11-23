#pragma once
#include <string>

namespace Schmog {

	struct TagComponent
	{
		TagComponent(std::string name)
			: Name(name) {}

		std::string Name;
	};
}