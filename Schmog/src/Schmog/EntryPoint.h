#pragma once

#ifdef SG_PLATFORM_WINDOWS
	
#include <memory>


extern std::shared_ptr<Schmog::Application>  Schmog::CreateApplication();

int main(int argc, char** argv)
{
	Schmog::Log::Init();
	SG_CORE_INFO("Logger started");

	auto app = Schmog::CreateApplication();
	app->Run();
}


#endif
