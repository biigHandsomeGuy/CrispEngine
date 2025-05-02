#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
namespace Crisp
{
	class CRISP_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent&);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be define in client
	Application* CreateApplication();
}