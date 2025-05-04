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
		if (Crisp::Input::IsKeyPressed(CR_KEY_TAB))
			CR_INFO("Tab key is pressed(poll)");
	}
	void OnEvent(Crisp::Event& event) override 
	{
		if (event.GetEventType() == Crisp::EventType::KeyPressed)
		{
			Crisp::KeyPressedEvent& e = (Crisp::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CR_KEY_TAB)
				CR_INFO("Tab key is pressed(event)");
			CR_INFO("{0}", (char)e.GetKeyCode());
		}

		// CR_TRACE("{0}", event.ToString());
	}

};

class Sandbox : public Crisp::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Crisp::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
