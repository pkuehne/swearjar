#include "logging.h"
#include <chrono>

namespace SwearJar {

LogManager* LogManager::instance = nullptr;

LogManager* LogManager::get() {
    if (instance == nullptr) {
        instance = new LogManager();
    }
    return instance;
}

void LogManager::reset() {
    if (instance != nullptr) {
        delete instance;
    }
}

LogManager::LogManager() : m_out(), m_null() {
    m_out.open("swearjar.log", std::ofstream::out);
}

void LogManager::threshold(LogLevel level) {
    m_level = level;
}

std::ostream& LogManager::log(LogLevel level) {
    if (level >= m_level) {
        return m_out;
    }
    return m_null;
}

Logger::Logger(LogLevel level, std::string file, int line)
    : m_stream(LogManager::get()->log(level)) {
    formatTimestamp();
    m_stream << " ";
    formatFile(file, line);
    m_stream << " ";
    formatLevel(level);
    m_stream << " ";
}

void Logger::formatTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto fraction =
        now - std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto millis =
        std::chrono::duration_cast<std::chrono::milliseconds>(fraction);
    time_t raw = std::chrono::system_clock::to_time_t(now);

    char formatted[20] = {0};
    strftime(static_cast<char*>(formatted), sizeof(formatted), "%T",
             localtime(&raw));
    m_stream << static_cast<char*>(formatted);
    m_stream << "." << millis.count();
}

void Logger::formatLevel(LogLevel level) {
    m_stream << "[";
    switch (level) {
        case LogLevel::Debug:
            m_stream << "DEBUG";
            break;
        case LogLevel::Info:
            m_stream << "INFO";
            break;
        case LogLevel::Warn:
            m_stream << "WARN";
            break;
        case LogLevel::Error:
            m_stream << "ERROR";
            break;
        default:
            break;
    }
    m_stream << "]";
}

void Logger::formatFile(const std::string& file, int line) {
    size_t lastSep = file.rfind('/');

    m_stream << file.substr(lastSep + 1, std::string::npos) << ":" << line;
}

std::ostream& Logger::output() {
    return m_stream;
}

Logger::~Logger() {
    m_stream << std::endl;
}

} // namespace SwearJar
