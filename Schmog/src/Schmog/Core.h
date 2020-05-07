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
