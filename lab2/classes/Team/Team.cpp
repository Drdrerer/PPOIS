#include <algorithm>
#include "Team.h"
#include "../RepairTask/RepairTask.h"
#include "../Material/Material.h"
#include <iostream>

Team::Team(const std::string& name) : teamName(name), teamLead(nullptr) {}

void Team::addMember(Master* master) {
    members.push_back(master);
    if (!teamLead) {
        teamLead = master;
    }
    std::cout << "Added " << master->getFullName() << " to team " << teamName << std::endl;
}

void Team::removeMember(Master* master) {
    auto it = std::find(members.begin(), members.end(), master);
    if (it != members.end()) {
        members.erase(it);
        std::cout << "Removed " << master->getFullName() << " from team " << teamName << std::endl;
    }
}

void Team::startTask(class RepairTask* task) {
    std::cout << "Team " << teamName << " started task: " << task->getDescription() << std::endl;
}

void Team::completeTask(class RepairTask* task) {
    std::cout << "Team " << teamName << " completed task: " << task->getDescription() << std::endl;
}

void Team::requestMaterials(class RepairTask* task, class Material* material, int quantity) {
    std::cout << "Team " << teamName << " requested " << quantity 
              << " of " << material->getName() << " for task" << std::endl;
}

double Team::calculateTeamProductivity() const {
    if (members.empty()) return 0.0;
    double totalProductivity = 0.0;
    for (auto member : members) {
        totalProductivity += member->getAvailability() ? 1.0 : 0.5;
    }
    return totalProductivity / members.size();
}

std::string Team::getTeamName() const {
    return teamName;
}
