#pragma once

extern Crisp::Application* Crisp::CreateApplication();

int main()
{
	Crisp::Log::Init();
	CR_CORE_INFO("Initialized Log!");

	auto app = Crisp::CreateApplication();


	app->Run();

	delete app;
	return 0;
}