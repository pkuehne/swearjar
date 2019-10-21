#include "logging.h"

namespace SwearJar {
std::ofstream Logging::out = std::ofstream();
LogLevel level = LogLevel::Debug;
} // namespace SwearJar
