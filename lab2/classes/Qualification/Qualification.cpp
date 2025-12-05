#include "Qualification.h"

Qualification::Qualification(const std::string& name, int level, const std::string& desc)
    : name(name), level(level), description(desc) {}

bool Qualification::requiresRenewal() const {
    return false;
}

std::string Qualification::getExpirationDate() const {
    return "2024-12-31";
}

bool Qualification::isValidForWork() const {
    return level > 0 && !name.empty();
}

std::string Qualification::getName() const {
    return name;
}

int Qualification::getLevel() const {
    return level;
}
