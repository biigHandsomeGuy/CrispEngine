#include <Crisp.h>

class ExampleLayer : public Crisp::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}
	void OnUpdate() override
	{
		CR_INFO("ExampleLayer::Update");
	}
	void OnEvent(Crisp::Event& event) override 
	{
		CR_TRACE("{0}", event.ToString());
	}

};

class Sandbox : public Crisp::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
