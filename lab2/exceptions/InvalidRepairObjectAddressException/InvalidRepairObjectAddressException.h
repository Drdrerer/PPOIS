#ifndef INVALIDREPAIROBJECTADDRESSEXCEPTION_H
#define INVALIDREPAIROBJECTADDRESSEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidRepairObjectAddressException : public std::runtime_error {
public:
    InvalidRepairObjectAddressException() : std::runtime_error("Invalid repair object address") {}
};

#endif
