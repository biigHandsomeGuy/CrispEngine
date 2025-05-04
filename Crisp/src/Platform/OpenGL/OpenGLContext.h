#pragma once

#include "Crisp/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Crisp
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}