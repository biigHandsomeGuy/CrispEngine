#pragma once

#include "Core.h"
#include "Window.h"
#include "Crisp/Events/Event.h"
#include "Crisp/Events/ApplicationEvent.h"
#include "Crisp/Core/LayerStack.h"
#include "Crisp/Core/TimeStep.h"
#include "Crisp/ImGui/ImGuiLayer.h"

#include "Crisp/Renderer/Shader.h"
#include "Crisp/Renderer/Buffer.h"
#include "Crisp/Renderer/VertexArray.h"
#include "Crisp/Renderer/OrthographicCamera.h"
namespace Crisp
{
	class CRISP_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent&);
		bool OnWindowResized(WindowResizeEvent&);

	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// to be define in client
	Application* CreateApplication();
}