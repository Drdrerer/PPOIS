#ifndef DUPLICATEEMPLOYEEIDEXCEPTION_H
#define DUPLICATEEMPLOYEEIDEXCEPTION_H

#include <stdexcept>
#include <string>

class DuplicateEmployeeIdException : public std::runtime_error {
public:
    DuplicateEmployeeIdException() : std::runtime_error("Duplicate employee ID") {}
};

#endif
