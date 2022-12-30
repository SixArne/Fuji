#pragma once

#ifdef FU_PLATFORM_WINDOWS
	#ifdef FU_BUILD_DLL
		#define FUJI_API __declspec(dllexport)
	#else
		#define FUJI_API __declspec(dllimport)
	#endif // DEBUG

#else
#error Fuji only supports Windows
#endif