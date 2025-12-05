#include <iostream>
#include "Master.h"

Master::Master(int id, const std::string& name, double salary)
    : Employee(id, name, salary), currentTeam(nullptr), isAvailable(true) {}

Master::~Master() {
    for (auto qual : qualifications) {
        delete qual;
    }
}

void Master::performWork() {
    performRepairWork();
}

void Master::upgradeQualification(Qualification* newQualification) {
    qualifications.push_back(newQualification);
    std::cout << "Qualification upgraded: " << newQualification->getName() << std::endl;
}

void Master::reportWorkHours(RepairTask* task, double hours) {
    std::cout << "Reported " << hours << " hours for task" << std::endl;
}

void Master::reportTaskProgress(RepairTask* task, int percentComplete) {
    std::cout << "Task progress: " << percentComplete << "%" << std::endl;
}

bool Master::getAvailability() const {
    return isAvailable;
}
