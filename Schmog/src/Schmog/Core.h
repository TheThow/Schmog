#pragma once

#ifdef SG_PLATFORM_WINDOWS
	#ifdef SG_BUILD_DLL
		#define SCHMOG_API  __declspec(dllexport)
	#else
		#define SCHMOG_API __declspec(dllimport)
	#endif 
#else
	#error Only Windows is supported
#endif

#ifdef SG_ENABLE_ASSERTS
#define SG_ASSERT(x, ...) { if(!(x)) { SG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SG_CORE_ASSERT(x, ...) { if(!(x)) { SG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SG_ASSERT(x, ...)
#define SG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

