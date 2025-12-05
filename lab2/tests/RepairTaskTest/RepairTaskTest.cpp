#include <gtest/gtest.h>
#include "../../classes/RepairTask/RepairTask.h"
#include "../../classes/Service/Service.h"

TEST(RepairTaskTest, ConstructorAndGetters) {
    Service service("Painting", "Wall painting", 8.0);
    RepairTask task("Paint living room", &service, 4.0);
    
    EXPECT_EQ(task.getDescription(), "Paint living room");
    EXPECT_EQ(task.getEstimatedHours(), 4.0);
}

TEST(RepairTaskTest, CalculateActualCost) {
    Service service("Painting", "Wall painting", 8.0);
    RepairTask task("Paint living room", &service, 4.0);
    
    double cost = task.calculateActualCost();
    EXPECT_GT(cost, 0.0);
}

TEST(RepairTaskTest, UpdateProgress) {
    Service service("Painting", "Wall painting", 8.0);
    RepairTask task("Paint living room", &service, 4.0);
    
    EXPECT_NO_THROW(task.updateProgress(50));
}

TEST(RepairTaskTest, IsCompleted) {
    Service service("Painting", "Wall painting", 8.0);
    RepairTask task("Paint living room", &service, 4.0);
    
    bool completed = task.isCompleted();
}
