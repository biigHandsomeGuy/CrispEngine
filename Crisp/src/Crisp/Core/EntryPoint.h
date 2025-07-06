#pragma once

extern Crisp::Application* Crisp::CreateApplication();

int main()
{
	Crisp::Log::Init();

	CR_PROFILE_BEGINE_SESSION("Startup", "CrispProfile-Startup.json");
	auto app = Crisp::CreateApplication();
	CR_PROFILE_END_SESSION();

	CR_PROFILE_BEGINE_SESSION("Runtime", "CrispProfile-Runtime.json");
	app->Run();
	CR_PROFILE_END_SESSION();

	delete app;
	return 0;
}