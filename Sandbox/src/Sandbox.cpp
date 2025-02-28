#include <Crisp.h>

class Sandbox : public Crisp::Application
{
public:
	Sandbox()
	{


	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
