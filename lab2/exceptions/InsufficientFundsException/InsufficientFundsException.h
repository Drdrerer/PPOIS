#ifndef INSUFFICIENTFUNDSEXCEPTION_H
#define INSUFFICIENTFUNDSEXCEPTION_H

#include <stdexcept>
#include <string>

class InsufficientFundsException : public std::runtime_error {
public:
    InsufficientFundsException() : std::runtime_error("Insufficient funds for payment") {}
};

#endif
