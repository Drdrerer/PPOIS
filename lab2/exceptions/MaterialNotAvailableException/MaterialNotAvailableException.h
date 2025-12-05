#ifndef MATERIALNOTAVAILABLEEXCEPTION_H
#define MATERIALNOTAVAILABLEEXCEPTION_H

#include <stdexcept>
#include <string>

class MaterialNotAvailableException : public std::runtime_error {
public:
    MaterialNotAvailableException(const std::string& material) 
        : std::runtime_error("Material not available: " + material) {}
};

#endif
