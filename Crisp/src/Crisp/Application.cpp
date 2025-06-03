#include "pch.h"

#include "Application.h"
#include "Input.h"
#include "Crisp/Renderer/Renderer.h"

#include <GLFW/glfw3.h>
namespace Crisp
{
	Application* Application::s_Instance = nullptr;

	

	Application::Application()
	{
		CR_CORE_ASSERT(!s_Instance, "Application already exist");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetVSync(false);
		m_Window->SetEventCallback([this](Event& e) 
			{
				OnEvent(e);
			});

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}



	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			auto [x, y] = Input::GetMousePosition();
			

			m_Window->OnUpdate();
		}
	}
	

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}

