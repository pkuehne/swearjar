#pragma once

#include <fstream>
#include <sstream>

#define FILE "" //__FILE__

#ifdef SJ_DISABLE_LOGGING
#define LOG_DEBUG std::stringstream()
#define LOG_INFO std::stringstream()
#define LOG_WARN std::stringstream()
#define LOG_ERROR std::stringstream()
#define LOG_END std::endl;
#else
#define LOG_DEBUG Logging::debug() << FILE
#define LOG_INFO Logging::info() << FILE
#define LOG_WARN Logging::warn() << FILE
#define LOG_ERROR Logging::error() << FILE
#define LOG_END std::endl;
#endif

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
    static std::ostream& log(std::string&& level) {
        if (!out.is_open()) {
            out.open("swearjar.log", std::ofstream::out);
        }
        out << "[" << level << "] ";
        return out;
    }
    static std::ostream& drop() {
        if (!null.is_open()) {
            null.open("/dev/null", std::ofstream::out);
        }
        return null;
    }
    static std::ostream& debug() {
        switch (level) {
            case LogLevel::None:
            case LogLevel::Debug:
                return log("DEBUG");
            case LogLevel::Info:
            case LogLevel::Warn:
            case LogLevel::Error:
            case LogLevel::All:
            default:
                break;
        }
        return drop();
    }
    static std::ostream& info() {
        switch (level) {
            case LogLevel::None:
            case LogLevel::Debug:
            case LogLevel::Info:
                return log("INFO");
            case LogLevel::Warn:
            case LogLevel::Error:
            case LogLevel::All:
            default:
                break;
        }
        return drop();
    }
    static std::ostream& warn() {
        switch (level) {
            case LogLevel::None:
            case LogLevel::Debug:
            case LogLevel::Info:
            case LogLevel::Warn:
                return log("WARN");
            case LogLevel::Error:
            case LogLevel::All:
            default:
                break;
        }
        return drop();
    }
    static std::ostream& error() {
        switch (level) {
            case LogLevel::None:
            case LogLevel::Debug:
            case LogLevel::Info:
            case LogLevel::Warn:
            case LogLevel::Error:
                return log("ERROR");
            case LogLevel::All:
            default:
                break;
        }
        return drop();
    }

private:
    static std::ofstream out;
    static std::ofstream null;
    static LogLevel level;
}; // namespace SwearJar

} // namespace SwearJar
