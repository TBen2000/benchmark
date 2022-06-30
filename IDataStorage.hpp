#pragma once
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class IDataStorage
{
public:
    // timestamp, event, component, rest as buffer
    virtual void store(const int event, const std::string component, const std::string buffer) = 0;
    virtual std::string getName() = 0;

protected:
    const std::string eventLookupTable[7] = {
        "Event0",
        "Event1",
        "Event2",
        "Event3",
        "Event4",
        "Event5",
        "Event6"};

    uint64_t nanosecondsSinceEpoch()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    std::string datetime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream stream;
        tm *tm_ = std::localtime(&in_time_t);

        stream << tm_->tm_year + 1900
        << std::setfill('0') << std::setw(2) << tm_->tm_mon + 1
        << std::setfill('0') << std::setw(2) << tm_->tm_mday
        << "T"
        << std::setfill('0') << std::setw(2) << tm_->tm_hour
        << std::setfill('0') << std::setw(2) << tm_->tm_min
        << std::setfill('0') << std::setw(2) << tm_->tm_sec;
        return stream.str();
    }
};
