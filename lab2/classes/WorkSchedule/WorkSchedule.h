#ifndef WORKSCHEDULE_H
#define WORKSCHEDULE_H

#include <string>
#include <vector>
#include "../WorkShift/WorkShift.h"
#include "../Team/Team.h"

class WorkSchedule {
private:
    std::string date;
    std::vector<WorkShift*> shifts;
    Team* assignedTeam;

public:
    WorkSchedule(const std::string& date, Team* team);
    ~WorkSchedule();
    
    void assignShift(class Employee* employee, WorkShift* shift);
    bool checkShiftConflicts(class Employee* employee, WorkShift* newShift) const;
    void optimizeShiftDistribution();
    std::string getDate() const;
    Team* getAssignedTeam() const;
};

#endif
