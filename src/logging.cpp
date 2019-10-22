#include "logging.h"
#include <chrono>

namespace SwearJar {
std::ofstream Logging::out = std::ofstream();
std::ofstream Logging::null = std::ofstream();
LogLevel Logging::level = LogLevel::Info;

std::ostream& Logging::log(const std::string& level) {
    if (!out.is_open()) {
        out.open("swearjar.log", std::ofstream::out);
    }
    add_timestamp();
    add_level(level);
    return out;
}

std::ostream& Logging::drop() {
    if (!null.is_open()) {
        null.open("/dev/null", std::ofstream::out);
    }
    return null;
}

void Logging::add_level(const std::string& level) {
    out << "[" << level << "] ";
}

void Logging::add_timestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto fraction = now - time_point_cast<seconds>(now);
    auto millis = duration_cast<milliseconds>(fraction);
    time_t raw = system_clock::to_time_t(now);

    char formatted[20] = {0};
    strftime(formatted, sizeof(formatted), "%T", localtime(&raw));
    out << formatted;
    out << "." << millis.count() << " ";
}

std::ostream& Logging::debug() {
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

std::ostream& Logging::info() {
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

std::ostream& Logging::warn() {
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

std::ostream& Logging::error() {
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

} // namespace SwearJar
