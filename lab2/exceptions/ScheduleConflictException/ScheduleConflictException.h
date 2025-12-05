#ifndef SCHEDULECONFLICTEXCEPTION_H
#define SCHEDULECONFLICTEXCEPTION_H

#include <stdexcept>
#include <string>

class ScheduleConflictException : public std::runtime_error {
public:
    ScheduleConflictException() : std::runtime_error("Schedule conflict detected") {}
};

#endif
