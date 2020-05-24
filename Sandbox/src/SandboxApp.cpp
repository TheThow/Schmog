#include <Schmog.h>
#include <memory>

#include <imgui/imgui.h>


class ExampleLayer : public Schmog::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate()
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
		PushLayer(std::make_shared<ExampleLayer>());
	}

	~Sandbox() 
	{

	}


};

std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
{
	return std::make_shared<Sandbox>();
}