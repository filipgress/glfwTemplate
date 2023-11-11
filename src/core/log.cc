#include "log.h"

namespace cg_core {

	std::mutex log_mutex;
	const std::string kLogFile { "action.log" };

	void Log(LogPriority priority, const std::string& prefix, const std::string& msg) {
		if (priority > LogPriority::kInfo)
			std::cerr << "[" << prefix << "] " << msg << std::endl;
		else
			std::cout << "[" << prefix << "] " << msg << std::endl;
		
		// in debug priority, don't log to file
		if (priority == LogPriority::kDebug)
			return;

		std::scoped_lock<std::mutex> lock(log_mutex);
		std::ofstream file(kLogFile, std::ios::app);

		if (!file.is_open()) {
			std::cerr << "Unable to open log file\n";
		} else {
			file << Timestamp() << " [" << prefix << "] " << msg << std::endl;
			file.close();
		}
	}

	std::string Timestamp() {
		auto now = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(now);

		std::ostringstream time;
		time << std::put_time(std::localtime(&t), "%d-%m-%Y %T");
		return time.str();
	}

}
