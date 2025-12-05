#ifndef QUALIFICATIONMISMATCHEXCEPTION_H
#define QUALIFICATIONMISMATCHEXCEPTION_H

#include <stdexcept>
#include <string>

class QualificationMismatchException : public std::runtime_error {
public:
    QualificationMismatchException() : std::runtime_error("Qualification mismatch for assigned task") {}
};

#endif
