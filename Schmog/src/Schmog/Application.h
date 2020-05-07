#pragma once
#include "Core.h"
#include <memory>

namespace Schmog {

	class SCHMOG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TO BE DEFINED IN CLIENT
	std::shared_ptr<Application> CreateApplication();

}