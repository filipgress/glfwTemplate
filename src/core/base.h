#ifndef BASE_H_
#define BASE_H_

#include "log.h"

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define PLATFROM_WINDOWS

#elif __linux__
	#define PLATFROM_LINUX

#else
	#error "Unsupported platform"
#endif

// Assert
#ifdef NDEBUG // release
	#define DEBUG_BREAK 
	#define ASSERT

#else					// debug
	#ifdef PLATFROM_LINUX
		#include <signal.h>
		#define DEBUG_BREAK() raise(SIGTRAP)

	#else
		#define DEBUG_BREAK() __debugbreak()
	#endif

	#define ASSERT(condition) \
		if (!(condition)) { \
			cg_core::Log(cg_core::LogPriority::kDebug, "ASSERT", MSG(#condition)); \
			DEBUG_BREAK(); \
		}
#endif 

// Utilities
#define BIT(x) (1 << x)

#endif // BASE_H_
