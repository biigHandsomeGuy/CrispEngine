#pragma once

#include <Windows.h>


extern Crisp::Application* Crisp::CreateApplication();

int WINAPI wWinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	PWSTR pCmdLine, 
	int nCmdShow)
{
	::AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "Hello\n";
	auto app = Crisp::CreateApplication();

	app->Run();

	delete app;
}