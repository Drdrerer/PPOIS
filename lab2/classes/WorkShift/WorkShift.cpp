#include <iostream>
#include "WorkShift.h"

WorkShift::WorkShift(const std::string& start, const std::string& end)
    : startTime(start), endTime(end) {}

double WorkShift::calculateDuration() const {
    return 8.0; 
}

bool WorkShift::checkOvertime() const {
    return calculateDuration() > 8.0;
}

void WorkShift::addAssignedMaster(Master* master) {
    assignedMasters.push_back(master);
    std::cout << "Added master to shift" << std::endl;
}

std::string WorkShift::getStartTime() const {
    return startTime;
}

std::string WorkShift::getEndTime() const {
    return endTime;
}
