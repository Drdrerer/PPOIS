#include <iostream>
#include "Plumber.h"

Plumber::Plumber(int id, const std::string& name, double salary)
    : Master(id, name, salary), completedTasksCount(0) {}

Plumber::~Plumber() {
    for (auto tool : specificTools) {
        delete tool;
    }
    for (auto spec : plumbingSpecialties) {
        delete spec;
    }
}

void Plumber::performRepairWork() {
    std::cout << "Plumber performing repair work" << std::endl;
    completedTasksCount++;
}

void Plumber::unclogPipe() {
    std::cout << "Unclogging pipe" << std::endl;
}

void Plumber::installPlumbingSystem() {
    std::cout << "Installing plumbing system" << std::endl;
}

void Plumber::repairFaucet() {
    std::cout << "Repairing faucet" << std::endl;
}
