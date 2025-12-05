#ifndef DOUBLEASSIGNMENTEXCEPTION_H
#define DOUBLEASSIGNMENTEXCEPTION_H

#include <stdexcept>
#include <string>

class DoubleAssignmentException : public std::runtime_error {
public:
    DoubleAssignmentException() : std::runtime_error("Employee already assigned to another task") {}
};

#endif
