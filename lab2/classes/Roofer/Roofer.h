#ifndef ROOFER_H
#define ROOFER_H

#include "../Master/Master.h"
#include <vector>

enum class RoofType { FLAT, GABLE, HIP, MANSARD };

class Roofer : public Master {
private:
    std::vector<RoofType> workedRoofTypes;
    int maxWorkingHeight;
    bool hasHeightWorkLicense;

public:
    Roofer(int id, const std::string& name, double salary, int maxHeight, bool license);
    
    void performRepairWork() override;
    void installRoof();
    void repairLeaks();
    void checkRoofStructure();
};

#endif
