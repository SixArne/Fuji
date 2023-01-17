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

#ifdef FU_ENABLE_ASSERTS
	#define FU_ASSERT(x, ...) { if(!(x)) { F_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FU_CORE_ASSERT(x, ...) { if(!(x)) { F_LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FU_ASSERT(x, ...)
	#define FU_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)