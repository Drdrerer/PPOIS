#include "Specialization.h"

Specialization::Specialization(const std::string& name, const std::string& area, Qualification* qual)
    : specializationName(name), area(area), requiredQualification(qual) {}

bool Specialization::meetsRequirements(Qualification* userQualification) const {
    return userQualification && userQualification->getLevel() >= requiredQualification->getLevel();
}

std::string Specialization::getSpecializationName() const {
    return specializationName;
}

std::string Specialization::getArea() const {
    return area;
}
