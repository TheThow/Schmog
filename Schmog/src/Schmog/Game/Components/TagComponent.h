#pragma once
#include <string>

namespace Schmog {

	struct TagComponent
	{
		TagComponent()
		{
			Name = "Entity";
		}

		TagComponent(std::string name)
			: Name(name) {}

		std::string Name;
	};
}