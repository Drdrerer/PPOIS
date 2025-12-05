#ifndef TASKALREADYCOMPLETEDEXCEPTION_H
#define TASKALREADYCOMPLETEDEXCEPTION_H

#include <stdexcept>
#include <string>

class TaskAlreadyCompletedException : public std::runtime_error {
public:
    TaskAlreadyCompletedException() : std::runtime_error("Task already completed") {}
};

#endif
