#include "pch.h"

#include "Application.h"

#include "Crisp/Events/ApplicationEvent.h"


#include <GLFW/glfw3.h>
namespace Crisp
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback([this](Event& e) 
			{
				OnEvent(e);
			});
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispather(e);
		dispather.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)
			{
				return OnWindowClosed(e);
			});


		CR_CORE_INFO("{0}", e.ToString());
	}



	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
	

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}

