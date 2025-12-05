#ifndef SPECIALIZATION_H
#define SPECIALIZATION_H

#include <string>
#include "../Qualification/Qualification.h"

class Specialization {
private:
    std::string specializationName;
    std::string area;
    Qualification* requiredQualification;

public:
    Specialization(const std::string& name, const std::string& area, Qualification* qual);
    
    bool meetsRequirements(Qualification* userQualification) const;
    std::string getSpecializationName() const;
    std::string getArea() const;
};

#endif
