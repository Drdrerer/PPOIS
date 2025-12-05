#include <iostream>
#include "Roofer.h"

Roofer::Roofer(int id, const std::string& name, double salary, int maxHeight, bool license)
    : Master(id, name, salary), maxWorkingHeight(maxHeight), hasHeightWorkLicense(license) {}

void Roofer::performRepairWork() {
    std::cout << "Roofer performing roof work" << std::endl;
}

void Roofer::installRoof() {
    std::cout << "Installing roof" << std::endl;
}

void Roofer::repairLeaks() {
    std::cout << "Repairing roof leaks" << std::endl;
}

void Roofer::checkRoofStructure() {
    std::cout << "Checking roof structure" << std::endl;
}
