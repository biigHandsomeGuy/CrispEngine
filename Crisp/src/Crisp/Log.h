#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Crisp {

	class CRISP_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


// Core log macros
#define CR_CORE_TRACE(...)    ::Crisp::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CR_CORE_INFO(...)     ::Crisp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CR_CORE_WARN(...)     ::Crisp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CR_CORE_ERROR(...)    ::Crisp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CR_CORE_CRITICAL(...) ::Crisp::Log::GetCoreLogger()->critical(__VA_ARGS__)
								
// Client log macros			
#define CR_TRACE(...)         ::Crisp::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CR_INFO(...)          ::Crisp::Log::GetClientLogger()->info(__VA_ARGS__)
#define CR_WARN(...)          ::Crisp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CR_ERROR(...)         ::Crisp::Log::GetClientLogger()->error(__VA_ARGS__)
#define CR_CRITICAL(...)      ::Crisp::Log::GetClientLogger()->critical(__VA_ARGS__)