#pragma once

#include <fstream>

#define LOG_DEBUG Logging::debug() << __FILE__ << ": "
#define LOG_INFO Logging::info() << __FILE__ << ": "
#define LOG_WARN Logging::warn() << __FILE__ << ": "
#define LOG_ERROR Logging::error() << __FILE__ << ": "

namespace SwearJar {

enum class LogLevel {
    All = 0,
    Debug,
    Info,
    Warn,
    Error,
    None,
};

class Logging {
public:
    static std::ofstream& log(std::string&& level) {
        if (!out.is_open()) {
            out.open("swearjar.log", std::ofstream::out);
        }
        out << "[" << level << "] ";
        return out;
    }
    static std::ofstream& debug() {
        return log("DEBUG");
    }
    static std::ofstream& info() {
        return log("INFO");
    }
    static std::ofstream& warn() {
        return log("WARN");
    }
    static std::ofstream& error() {
        return log("ERROR");
    }

private:
    static std::ofstream out;
    static LogLevel level;
};

} // namespace SwearJar
