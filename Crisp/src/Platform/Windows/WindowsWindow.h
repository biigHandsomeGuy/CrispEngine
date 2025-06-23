#pragma once

#include "Crisp/Core/Window.h"
#include "Crisp/Renderer/GraphicsContext.h"

struct GLFWwindow;


namespace Crisp
{
	class CRISP_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		~WindowsWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return m_Data.Width; };
		inline uint32_t GetHeight() const override { return m_Data.Height; };

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}