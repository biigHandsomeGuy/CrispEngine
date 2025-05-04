#pragma once

#if CR_DYNAMIC_LINK
	#ifdef CR_BUILD_DLL
		#define CRISP_API __declspec(dllexport)
	#else
		#define CRISP_API __declspec(dllimport)
	#endif // CR_BUILD_DLL
#else
	#define CRISP_API
#endif


#ifdef CR_ENABLE_ASSERTS
	#define CR_ASSERT(x, ...) { if(!(x)) { CR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CR_CORE_ASSERT(x, ...) { if(!(x)) { CR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CR_ASSERT(x, ...)
	#define CR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)