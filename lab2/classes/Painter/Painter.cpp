#include <iostream>
#include "Painter.h"

Painter::Painter(int id, const std::string& name, double salary, double consumptionRate)
    : Master(id, name, salary), paintConsumptionRate(consumptionRate) {}

Painter::~Painter() {
    for (auto sprayer : sprayers) {
        delete sprayer;
    }
}

void Painter::performRepairWork() {
    std::cout << "Painter performing painting work" << std::endl;
}

void Painter::paintSurface() {
    std::cout << "Painting surface" << std::endl;
}

void Painter::mixColors() {
    std::cout << "Mixing paint colors" << std::endl;
}

void Painter::calculatePaintRequired(double area) {
    double required = area * paintConsumptionRate;
    std::cout << "Paint required: " << required << " liters" << std::endl;
}
