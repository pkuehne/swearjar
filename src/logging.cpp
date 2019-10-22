#include "logging.h"

namespace SwearJar {
std::ofstream Logging::out = std::ofstream();
std::ofstream Logging::null = std::ofstream();
LogLevel Logging::level = LogLevel::Info;
} // namespace SwearJar
