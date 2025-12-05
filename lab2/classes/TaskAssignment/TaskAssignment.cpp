#include <iostream>
#include "TaskAssignment.h"

TaskAssignment::TaskAssignment(Master* master, RepairTask* task, const std::string& date)
    : master(master), task(task), assignmentDate(date) {}

void TaskAssignment::updateProgress(const std::string& progressNote) {
    std::cout << "Progress note: " << progressNote << std::endl;
}

void TaskAssignment::markAsCompleted() {
    std::cout << "Task marked as completed" << std::endl;
}

bool TaskAssignment::isOverdue() const {
    return false;
}

Master* TaskAssignment::getAssignedMaster() const {
    return master;
}

RepairTask* TaskAssignment::getAssignedTask() const {
    return task;
}
