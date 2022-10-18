#ifndef _LIB_LOG_INCLUDE_LOG_LOG_H_
#define _LIB_LOG_INCLUDE_LOG_LOG_H_

#include <stdint.h>

#include <ostream>
#include <string>
#include <sstream>
#include <type_traits>

namespace logistreamer
{
enum class Severity
{
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger
{
public:
    class Message
    {
    public:
        Message(Logger& logger, Severity severity) : logger_{logger}, severity_{severity}, msg_{} {}
        Message(Message const&) = default;
        Message(Message&& ) = default;
        ~Message();

        Message& append(std::string const& msg);

        Message& operator << (std::string const& s);
        Message& operator << (char const* s) { return this->operator<<(std::string{s}); }
        Message& operator << (int64_t i);
        Message& operator << (int32_t i)  { return this->operator<<(static_cast<int64_t>(i)); };
        Message& operator << (uint32_t i) { return this->operator<<(static_cast<int64_t>(i)); };
        Message& operator << (uint64_t i) { return this->operator<<(static_cast<int64_t>(i)); };
        Message& operator << (double d);
    private:
        Logger& logger_;
        Severity severity_;
        std::stringstream msg_;
    };

    Logger(std::ostream& stream, Severity min_visible_severity = Severity::WARN);
    ~Logger();

    Message message(Severity severity);
    void print(Severity severity, std::string msg);

    void setMinVisibleSeverity(Severity min_visible_severity) { min_visible_severity_ = min_visible_severity; }
private:
    std::ostream& ostream_;
    Severity min_visible_severity_;
};

Logger& getDefaultLogger();
}

#define LOG_INFO logistreamer::getDefaultLogger().message(logistreamer::Severity::INFO)
#define LOG_WARN logistreamer::getDefaultLogger().message(logistreamer::Severity::WARN)
#define LOG_ERROR logistreamer::getDefaultLogger().message(logistreamer::Severity::ERROR)
#define LOG_FATAL logistreamer::getDefaultLogger().message(logistreamer::Severity::FATAL)

#endif // _LIB_LOG_INCLUDE_LOG_LOG_H_