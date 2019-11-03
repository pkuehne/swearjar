#pragma once

#include <fstream>
#include <memory>
#include <sstream>

#define LOG_LINE(level)                                                        \
    for (bool r = true; r; r = false)                                          \
        for (Logger logger(level, __FILE__, __LINE__); r; r = false)           \
    logger.output()

#ifdef SJ_DISABLE_LOGGING
#define LOG_DEBUG std::stringstream()
#define LOG_INFO std::stringstream()
#define LOG_WARN std::stringstream()
#define LOG_ERROR std::stringstream()
#define LOG_FORCE std::stringstream()
#define LOG_END std::endl;
#else
#define LOG_DEBUG LOG_LINE(LogLevel::Debug)
#define LOG_INFO LOG_LINE(LogLevel::Info)
#define LOG_WARN LOG_LINE(LogLevel::Warn)
#define LOG_ERROR LOG_LINE(LogLevel::Error)
#define LOG_FORCE LOG_LINE(LogLevel::Force)
#define LOG_END ""
#endif

namespace SwearJar {

enum class LogLevel {
    All = 0,
    Debug,
    Info,
    Warn,
    Error,
    Force,
    None,
};

class LogManager {
public:
    static LogManager* get();
    static void reset();

    void threshold(LogLevel level);
    LogLevel threshold();
    std::ostream& log(LogLevel level);
    void enabled(bool enabled);
    bool enabled();

private:
    LogManager() = default;
    static std::unique_ptr<LogManager> instance;

private:
    LogLevel m_level = LogLevel::Warn;
    std::ofstream m_out;
    std::stringstream m_null;
    bool m_enabled = false;
};

class Logger {
public:
    Logger(LogLevel level, const std::string& file, int line);
    ~Logger();
    std::ostream& output();

    void formatTimestamp();
    void formatLevel(LogLevel level);
    void formatFile(const std::string& file, int line);

private:
    std::ostream& m_stream;
};

} // namespace SwearJar
