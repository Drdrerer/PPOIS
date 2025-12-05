#ifndef INVALIDORDERSTATUSEXCEPTION_H
#define INVALIDORDERSTATUSEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidOrderStatusException : public std::runtime_error {
public:
    InvalidOrderStatusException() : std::runtime_error("Invalid order status for operation") {}
};

#endif
