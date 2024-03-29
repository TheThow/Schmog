#include "sgpch.h"
#include "Log.h"

namespace Schmog {

	std::shared_ptr <spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr <spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{

		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			sinks[0]->set_pattern("%^[%T] %n: %v%$");
			sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/core.log", true));
			s_CoreLogger = std::make_shared<spdlog::logger>("SCHMOG", begin(sinks), end(sinks));

#ifdef SG_DEBUG
			s_CoreLogger->set_level(spdlog::level::trace);
			s_CoreLogger->flush_on(spdlog::level::trace);
#else 
			s_CoreLogger->set_level(spdlog::level::info);
			s_CoreLogger->flush_on(spdlog::level::err);
#endif

		}


		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			sinks[0]->set_pattern("%^[%T] %n: %v%$");
			sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app.log", true));
			s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(sinks), end(sinks));

#ifdef SG_DEBUG
			s_ClientLogger->set_level(spdlog::level::trace);
			s_ClientLogger->flush_on(spdlog::level::trace);
#else 
			s_ClientLogger->set_level(spdlog::level::info);
			s_ClientLogger->flush_on(spdlog::level::err);
#endif
		}

	}
}