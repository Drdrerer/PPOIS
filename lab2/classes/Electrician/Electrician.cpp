#include <iostream>
#include "Electrician.h"

Electrician::Electrician(int id, const std::string& name, double salary, int maxVoltage)
    : Master(id, name, salary), maxAllowedVoltage(maxVoltage), safetyGroup("Basic") {}

Electrician::~Electrician() {
    for (auto spec : electricalSpecialties) {
        delete spec;
    }
}

void Electrician::performRepairWork() {
    std::cout << "Electrician performing electrical work" << std::endl;
}

void Electrician::installWiring() {
    std::cout << "Installing electrical wiring" << std::endl;
}

void Electrician::repairCircuit() {
    std::cout << "Repairing electrical circuit" << std::endl;
}

void Electrician::checkElectricalSafety() {
    std::cout << "Checking electrical safety" << std::endl;
}
