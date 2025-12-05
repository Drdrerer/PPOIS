#include <iostream>
#include "Carpenter.h"

Carpenter::Carpenter(int id, const std::string& name, double salary, bool furnitureSkills)
    : Master(id, name, salary), canMakeFurniture(furnitureSkills) {}

Carpenter::~Carpenter() {
    for (auto tool : woodworkingTools) {
        delete tool;
    }
}

void Carpenter::performRepairWork() {
    std::cout << "Carpenter performing woodwork" << std::endl;
}

void Carpenter::buildFurniture() {
    if (canMakeFurniture) {
        std::cout << "Building furniture" << std::endl;
    }
}

void Carpenter::installWoodenStructures() {
    std::cout << "Installing wooden structures" << std::endl;
}

void Carpenter::repairWoodwork() {
    std::cout << "Repairing woodwork" << std::endl;
}
