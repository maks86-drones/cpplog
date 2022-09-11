#include "log/log.h"

#include <iostream>

namespace logistreamer
{
namespace {
std::string const kSeverityInfo{"[INFO]"};
std::string const kSeverityWarn{"[WARN]"};
std::string const kSeverityError{"[ERROR]"};
std::string const kSeverityFatal{"[FATAL]"};


std::string const& severityToStr(Severity severity)
{
    switch (severity)
    {
    case Severity::INFO:
        return kSeverityInfo;
    case Severity::WARN:
        return kSeverityWarn;
    case Severity::ERROR:
        return kSeverityError;    
    default:
        return kSeverityFatal;
    }
}
}

Logger::Message::~Message() {
    logger_.print(severity_, msg_.str());
}

Logger::Message& Logger::Message::append(std::string const& msg)
{
    msg_ << msg;
    return *this;
}

Logger::Message& Logger::Message::operator << (std::string const& s)
{
    msg_ << s;
    return *this;
}

Logger::Message& Logger::Message::operator << (int64_t i)
{
    msg_ << i;
    return *this;
}

Logger::Message& Logger::Message::operator << (double d)
{
    msg_ << d;
    return *this;
}


Logger::Logger(std::ostream& ostream) : ostream_{ostream}
{

}

Logger::~Logger()
{

}

Logger::Message Logger::message(Severity severity)
{
    return Message{*this, severity};
}

void Logger::print(Severity severity, std::string msg)
{
    ostream_ << severityToStr(severity) << " " << msg << std::endl;
    if (severity == Severity::FATAL)
    {
        std::abort();
    }
}

Logger& getDefaultLogger()
{
    static Logger logger{std::cerr};
    return logger;
}

}