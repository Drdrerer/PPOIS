#ifndef REPAIRTASK_H
#define REPAIRTASK_H

#include <string>
#include "../Service/Service.h"

class RepairTask {
private:
    std::string description;
    Service* service;
    double estimatedHours;

public:
    RepairTask(const std::string& desc, Service* serv, double hours);
    
    double calculateActualCost() const;
    void updateProgress(int percent);
    bool isCompleted() const;
    std::string getDescription() const;
    double getEstimatedHours() const;
};

#endif
