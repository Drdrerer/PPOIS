#ifndef MASTER_H
#define MASTER_H

#include "../Employee/Employee.h"
#include <vector>
#include "../Qualification/Qualification.h"

class Team;
class RepairTask;

class Master : public Employee {
protected:
    std::vector<Qualification*> qualifications;
    Team* currentTeam;
    bool isAvailable;

public:
    Master(int id, const std::string& name, double salary);
    virtual ~Master();
    
    void performWork() override;
    virtual void performRepairWork() = 0;
    void upgradeQualification(Qualification* newQualification);
    void reportWorkHours(RepairTask* task, double hours);
    void reportTaskProgress(RepairTask* task, int percentComplete);
    bool getAvailability() const;
};

#endif
