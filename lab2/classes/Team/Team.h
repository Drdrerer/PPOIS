#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include "../Master/Master.h"

class Team {
private:
    std::string teamName;
    std::vector<Master*> members;
    Master* teamLead;

public:
    Team(const std::string& name);
    
    void addMember(Master* master);
    void removeMember(Master* master);
    void startTask(class RepairTask* task);
    void completeTask(class RepairTask* task);
    void requestMaterials(class RepairTask* task, class Material* material, int quantity);
    double calculateTeamProductivity() const;
    std::string getTeamName() const;
};

#endif
