#ifndef LOG_H_
#define LOG_H_

// Generate (log) message with current filename and line position
#define MSG(...)			cg_core::CreateMsg(__FILE__, __LINE__, __VA_ARGS__)

#ifdef NDEBUG // release
	#define DEBUG(...) 
#else					// debug
	#define DEBUG(...)	cg_core::Log(cg_core::LogPriority::kDebug, "DEBUG", MSG(__VA_ARGS__))
#endif

#define INFO(...)			cg_core::Log(cg_core::LogPriority::kInfo, "INFO", MSG(__VA_ARGS__))
#define WARNING(...)	cg_core::Log(cg_core::LogPriority::kWarning, "WARNING", MSG(__VA_ARGS__))
#define ERROR(msg)		cg_core::Log(cg_core::LogPriority::kError, "ERROR", msg)

namespace cg_core {

	template <typename T>
	void CreateMsgRec(std::ostringstream& msg, T param) {
		msg << param;
	}

	template <typename T, typename... Args>
	void CreateMsgRec(std::ostringstream& msg, T param, Args... args) {
		msg << param;
		CreateMsgRec(msg, args...);
	}

	template <typename... Args>
	std::string CreateMsg(const std::string& filepath, uint16_t line, Args... args) {
		std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
		std::ostringstream msg;

		msg << filename << ": " << line << " | ";

		CreateMsgRec(msg, args...);
		return msg.str();
	}

	/*
	 * Debug:									log to console, strip away in release mode
	 * Error, Warning, Info:	log to console and log file
	 */

	enum class LogPriority { 
		kDebug = 0, 
		kInfo, 
		kWarning, 
		kError 
	};

	void Log(LogPriority priority, const std::string& prefix, const std::string& msg);
	std::string Timestamp();

}

#endif // LOG_H_
