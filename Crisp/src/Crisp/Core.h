#pragma once

#ifdef CR_BUILD_DLL
	#define CRISP_API __declspec(dllexport)
#else
	#define CRISP_API __declspec(dllimport)
#endif // CR_BUILD_DLL

#define BIT(x) (1 << x)