#include <iostream>
#include "WorkSchedule.h"

WorkSchedule::WorkSchedule(const std::string& date, Team* team)
    : date(date), assignedTeam(team) {}

WorkSchedule::~WorkSchedule() {
    for (auto shift : shifts) {
        delete shift;
    }
}

void WorkSchedule::assignShift(class Employee* employee, WorkShift* shift) {
    shifts.push_back(shift);
    std::cout << "Assigned shift to " << employee->getFullName() << std::endl;
}

bool WorkSchedule::checkShiftConflicts(class Employee* employee, WorkShift* newShift) const {
    return false;
}

void WorkSchedule::optimizeShiftDistribution() {
    std::cout << "Optimizing shift distribution" << std::endl;
}

std::string WorkSchedule::getDate() const {
    return date;
}

Team* WorkSchedule::getAssignedTeam() const {
    return assignedTeam;
}
