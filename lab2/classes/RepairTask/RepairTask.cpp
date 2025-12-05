#include <iostream>
#include "RepairTask.h"

RepairTask::RepairTask(const std::string& desc, Service* serv, double hours)
    : description(desc), service(serv), estimatedHours(hours) {}

double RepairTask::calculateActualCost() const {
    return estimatedHours * 50.0;
}

void RepairTask::updateProgress(int percent) {
    std::cout << "Task progress updated to " << percent << "%" << std::endl;
}

bool RepairTask::isCompleted() const {
    return false;
}

std::string RepairTask::getDescription() const {
    return description;
}

double RepairTask::getEstimatedHours() const {
    return estimatedHours;
}
