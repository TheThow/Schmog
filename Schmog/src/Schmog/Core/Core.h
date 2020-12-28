#pragma once

#include <memory>

#ifdef SG_PLATFORM_WINDOWS
	#if SG_DYNAMIC_LINK
		#ifdef SG_BUILD_DLL
			#define SCHMOG_API  __declspec(dllexport)
		#else
			#define SCHMOG_API __declspec(dllimport)
		#endif 
	#else 
		#define SCHMOG_API
	#endif

	#define NOMINMAX   

#else
	#error Only Windows is supported
#endif

#ifdef SG_DEBUG
	#define SG_ENABLE_ASSERTS
#endif

#ifdef SG_ENABLE_ASSERTS
#define SG_ASSERT(x, ...) { if(!(x)) { SG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SG_CORE_ASSERT(x, ...) { if(!(x)) { SG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SG_CORE_ASSERT(x, ...)
#define SG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define SG_PROFILE 1


namespace Schmog {

	template<typename T>
	using SharedRef = std::shared_ptr<T>;

}

