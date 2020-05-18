#include <Schmog.h>
#include <memory>


class ExampleLayer : public Schmog::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}
		

	void OnEvent(Schmog::Event& e)
	{
		//SG_TRACE("{0} - {1}", m_DebugName, e);
	}
};


class Sandbox : public Schmog::Application
{
public: 
	Sandbox()
	{
		auto gameLayer = std::make_shared<ExampleLayer>();
		PushLayer(gameLayer);
	}

	~Sandbox() 
	{

	}


};

std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
{
	return std::make_shared<Sandbox>();
}