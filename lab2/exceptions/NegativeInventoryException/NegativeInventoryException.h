#ifndef NEGATIVEINVENTORYEXCEPTION_H
#define NEGATIVEINVENTORYEXCEPTION_H

#include <stdexcept>
#include <string>

class NegativeInventoryException : public std::runtime_error {
public:
    NegativeInventoryException() : std::runtime_error("Inventory cannot be negative") {}
};

#endif
