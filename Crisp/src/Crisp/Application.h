#pragma once

#include "Core.h"
#include "Events/Event.h"
namespace Crisp
{
	class CRISP_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// to be define in client
	Application* CreateApplication();
}