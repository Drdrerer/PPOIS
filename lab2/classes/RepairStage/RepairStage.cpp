#include <iostream>
#include "RepairStage.h"
#include "../Master/Master.h"

RepairStage::RepairStage(const std::string& name, double cost) 
    : stageName(name), stageCost(cost) {}

RepairStage::~RepairStage() {
    for (auto material : usedMaterials) {
        delete material;
    }
}

void RepairStage::addUsedMaterial(Material* material, double quantity) {
    usedMaterials.push_back(material);
    std::cout << "Added material: " << material->getName() << std::endl;
}

void RepairStage::recordWorkedHours(class Master* master, double hours) {
    std::cout << "Recorded " << hours << " hours from " << master->getFullName() << std::endl;
}

bool RepairStage::validateStageCompletion() const {
    return !usedMaterials.empty();
}

std::string RepairStage::getStageName() const {
    return stageName;
}

double RepairStage::getStageCost() const {
    return stageCost;
}
