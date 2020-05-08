#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Schmog {

	class SCHMOG_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr <spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr <spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr <spdlog::logger> s_CoreLogger;
		static std::shared_ptr <spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define SG_CORE_FATAL(...)		::Schmog::Log::getCoreLogger()->fatal(__VA_ARGS__)
#define SG_CORE_ERROR(...)		::Schmog::Log::getCoreLogger()->error(__VA_ARGS__)
#define SG_CORE_WARN(...)		::Schmog::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SG_CORE_INFO(...)		::Schmog::Log::getCoreLogger()->info(__VA_ARGS__)
#define SG_CORE_TRACE(...)		::Schmog::Log::getCoreLogger()->trace(__VA_ARGS__)


// Client log macros
#define SG_FATAL(...)			::Schmog::Log::getClientLogger()->fatal(__VA_ARGS__)
#define SG_ERROR(...)			::Schmog::Log::getClientLogger()->error(__VA_ARGS__)
#define SG_WARN(...)			::Schmog::Log::getClientLogger()->warn(__VA_ARGS__)
#define SG_INFO(...)			::Schmog::Log::getClientLogger()->info(__VA_ARGS__)
#define SG_TRACE(...)			::Schmog::Log::getClientLogger()->trace(__VA_ARGS__)

