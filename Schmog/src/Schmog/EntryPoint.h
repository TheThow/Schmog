#pragma once

#ifdef SG_PLATFORM_WINDOWS
	
#include <memory>


extern std::shared_ptr<Schmog::Application>  Schmog::CreateApplication();

int main(int argc, char** argv)
{
	Schmog::Log::Init();
	Schmog::Log::getCoreLogger()->info("Initialized core log");
	Schmog::Log::getClientLogger()->info("Initialized client log");

	auto app = Schmog::CreateApplication();
	app->Run();
}


#endif
