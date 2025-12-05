#ifndef REPAIRSTAGE_H
#define REPAIRSTAGE_H

#include <string>
#include <vector>
#include "../Material/Material.h"

class RepairStage {
private:
    std::string stageName;
    std::vector<Material*> usedMaterials;
    double stageCost;

public:
    RepairStage(const std::string& name, double cost);
    ~RepairStage();
    
    void addUsedMaterial(Material* material, double quantity);
    void recordWorkedHours(class Master* master, double hours);
    bool validateStageCompletion() const;
    std::string getStageName() const;
    double getStageCost() const;
};

#endif
