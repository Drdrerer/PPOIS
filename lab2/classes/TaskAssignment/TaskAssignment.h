#ifndef TASKASSIGNMENT_H
#define TASKASSIGNMENT_H

#include <string>
#include "../Master/Master.h"
#include "../RepairTask/RepairTask.h"

class TaskAssignment {
private:
    Master* master;
    RepairTask* task;
    std::string assignmentDate;

public:
    TaskAssignment(Master* master, RepairTask* task, const std::string& date);
    
    void updateProgress(const std::string& progressNote);
    void markAsCompleted();
    bool isOverdue() const;
    Master* getAssignedMaster() const;
    RepairTask* getAssignedTask() const;
};

#endif
