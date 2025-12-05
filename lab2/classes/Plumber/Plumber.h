#ifndef PLUMBER_H
#define PLUMBER_H

#include "../Master/Master.h"
#include <vector>
#include "../Specialization/Specialization.h"
#include "../Tool/Tool.h"

class Plumber : public Master {
private:
    std::vector<Specialization*> plumbingSpecialties;
    std::vector<Tool*> specificTools;
    int completedTasksCount;

public:
    Plumber(int id, const std::string& name, double salary);
    ~Plumber();
    
    void performRepairWork() override;
    void unclogPipe();
    void installPlumbingSystem();
    void repairFaucet();
};

#endif
