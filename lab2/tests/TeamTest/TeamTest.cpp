#include <gtest/gtest.h>
#include "../../classes/Team/Team.h"
#include "../../classes/Plumber/Plumber.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"
#include "../../classes/Service/Service.h"
#include "../../classes/RepairTask/RepairTask.h"

TEST(TeamTest, ConstructorAndGetters) {
    Team team("Alpha Team");
    EXPECT_EQ(team.getTeamName(), "Alpha Team");
}

TEST(TeamTest, AddRemoveMember) {
    Team team("Alpha Team");
    Plumber* plumber = new Plumber(1, "Mike Plumber", 40000.0);
    
    team.addMember(plumber);
    
    team.removeMember(plumber);
}

TEST(TeamTest, CalculateTeamProductivity) {
    Team team("Alpha Team");
    Plumber* plumber = new Plumber(1, "Mike Plumber", 40000.0);
    team.addMember(plumber);
    
    double productivity = team.calculateTeamProductivity();
    EXPECT_GE(productivity, 0.0);
    EXPECT_LE(productivity, 1.0);
}

TEST(TeamTest, TeamOperations) {
    Team team("Alpha Team");
    
    MaterialCategory category("Test", "Test");
    Material material("Test Material", &category, "kg");
    Service service("Test Service", "Description", 5.0);
    RepairTask task("Test Task", &service, 2.0);
    EXPECT_NO_THROW(team.startTask(&task));
    EXPECT_NO_THROW(team.completeTask(&task));
    EXPECT_NO_THROW(team.requestMaterials(&task, &material, 10));
}
