#include "sgpch.h"
#include "Log.h"

namespace Schmog {

	std::shared_ptr <spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr <spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//spdlog::set_pattern("%^[%T] %n: %v%$");
		//s_CoreLogger = spdlog::stdout_color_mt("SCHMOG");
		//s_CoreLogger->set_level(spdlog::level::trace);

		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			sinks[0]->set_pattern("%^[%T] %n: %v%$");
			sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/core_log.txt", true));
			s_CoreLogger = std::make_shared<spdlog::logger>("SCHMOG", begin(sinks), end(sinks));
			s_CoreLogger->set_level(spdlog::level::trace);
			s_CoreLogger->flush_on(spdlog::level::warn);
		}



		//spdlog::set_pattern("%^[%T] %n: %v%$");
		//s_ClientLogger = spdlog::stdout_color_mt("APP");
		//s_ClientLogger->set_level(spdlog::level::trace);

		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			sinks[0]->set_pattern("%^[%T] %n: %v%$");
			sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app_log.txt", true));
			s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(sinks), end(sinks));
			s_ClientLogger->set_level(spdlog::level::trace);
			s_ClientLogger->flush_on(spdlog::level::warn);
		}

	}
}