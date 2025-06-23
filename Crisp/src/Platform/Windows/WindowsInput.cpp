#include "pch.h"
#include "WindowsInput.h"

#include "Crisp/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Crisp
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseBottonPressedImpl(int botton)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, botton);
		return state == GLFW_PRESS;
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto v = GetMousePositionImpl();

		return std::get<0>(v);
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto v = GetMousePositionImpl();

		return std::get<1>(v);
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}