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

#define LLOG_INFO                                                              \
    for (bool r = true; r; r = false)                                          \
        for (Logger logger(LogLevel::Info, __FILE__, __LINE__); r; r = false)  \
    logger.output()

namespace SwearJar {

enum class LogLevel {
    All = 0,
    Debug,
    Info,
    Warn,
    Error,
    None,
};

class LogManager {
public:
    static LogManager* get();
    static void reset();

    void threshold(LogLevel level);
    std::ostream& log(LogLevel level);

private:
    LogManager();
    static LogManager* instance;

private:
    LogLevel m_level = LogLevel::Warn;
    std::ofstream m_out;
    std::stringstream m_null;
};

class Logger {
public:
    Logger(LogLevel level, std::string file, int line);
    ~Logger();
    std::ostream& output();

    void formatTimestamp();
    void formatLevel(LogLevel level);
    void formatFile(const std::string& file, int line);

private:
    std::ostream& m_stream;
};

class Logging {
public:
    static std::ostream& log(const std::string& level);
    static std::ostream& drop();
    static void add_level(const std::string& level);
    static void add_timestamp();
    static std::ostream& debug();
    static std::ostream& info();
    static std::ostream& warn();
    static std::ostream& error();

private:
    static std::ofstream out;
    static std::ofstream null;
    static LogLevel level;
};

} // namespace SwearJar
