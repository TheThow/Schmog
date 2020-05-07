#include <Schmog.h>
#include <memory>

class Sandbox : public Schmog::Application
{
public: 
	Sandbox()
	{

	}

	~Sandbox() 
	{

	}


};

std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
{
	return std::make_shared<Sandbox>();
}