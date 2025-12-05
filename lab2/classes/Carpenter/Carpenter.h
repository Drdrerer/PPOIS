#ifndef CARPENTER_H
#define CARPENTER_H

#include "../Master/Master.h"
#include <vector>
#include "../Tool/Tool.h"

enum class WoodType { OAK, PINE, MAPLE, BIRCH };

class Carpenter : public Master {
private:
    std::vector<WoodType> workedWoodTypes;
    std::vector<Tool*> woodworkingTools;
    bool canMakeFurniture;

public:
    Carpenter(int id, const std::string& name, double salary, bool furnitureSkills);
    ~Carpenter();
    
    void performRepairWork() override;
    void buildFurniture();
    void installWoodenStructures();
    void repairWoodwork();
};

#endif
