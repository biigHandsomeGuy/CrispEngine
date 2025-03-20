#include "pch.h"

#include "Application.h"

#include "Crisp/Log.h"
#include "Crisp/Events/ApplicationEvent.h"

namespace Crisp
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1080, 720);
		CR_TRACE(e.ToString());
		// while (true)
		// { }
	}
}

