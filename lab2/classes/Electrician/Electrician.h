#ifndef ELECTRICIAN_H
#define ELECTRICIAN_H

#include "../Master/Master.h"
#include <vector>
#include "../Specialization/Specialization.h"

class Electrician : public Master {
private:
    int maxAllowedVoltage;
    std::vector<Specialization*> electricalSpecialties;
    std::string safetyGroup;

public:
    Electrician(int id, const std::string& name, double salary, int maxVoltage);
    ~Electrician();
    
    void performRepairWork() override;
    void installWiring();
    void repairCircuit();
    void checkElectricalSafety();
};

#endif
