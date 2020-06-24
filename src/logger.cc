
#include "logger.h"


void Logger::startLogging() {
	//logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

	logging::add_file_log
	(
		keywords::file_name = "log/SYSLOG_%N.txt",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = (
			expr::stream
				<< "[" << time_stamp << "]    ThreadID:["
				<< thread_id << "] Severity:["
				<< severity << "] "
				<< expr::if_(expr::has_attr(ip_addr))
					[
						expr::stream << "IP Address:[" << ip_addr << "] "
					]
				<< expr::smessage
		),
		keywords::auto_flush = true
	);

	logging::add_console_log
	(
		std::cout,
		keywords::format = (
			expr::stream
				<< "[" << time_stamp << "]    ThreadID:["
				<< thread_id << "] Severity:["
				<< severity << "] "
				<< expr::if_(expr::has_attr(ip_addr))
					[
						expr::stream << "IP Address:[" << ip_addr << "] "
					]
				<< expr::smessage
		)
	);

	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);

	logging::add_common_attributes();
}
