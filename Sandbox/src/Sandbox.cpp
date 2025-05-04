#include <Crisp.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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
	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
