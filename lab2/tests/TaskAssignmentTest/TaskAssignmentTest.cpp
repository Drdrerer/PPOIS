#include <gtest/gtest.h>
#include "../../classes/TaskAssignment/TaskAssignment.h"
#include "../../classes/Plumber/Plumber.h"
#include "../../classes/RepairTask/RepairTask.h"
#include "../../classes/Service/Service.h"

TEST(TaskAssignmentTest, ConstructorAndGetters) {
    Plumber master(1, "Mike Plumber", 40000.0);
    Service service("Plumbing", "Pipe repair", 2.0);
    RepairTask task("Fix pipe", &service, 2.0);
    
    TaskAssignment assignment(&master, &task, "2024-01-01");
    
    EXPECT_NE(assignment.getAssignedMaster(), nullptr);
    EXPECT_NE(assignment.getAssignedTask(), nullptr);
}

TEST(TaskAssignmentTest, UpdateProgress) {
    Plumber master(1, "Mike Plumber", 40000.0);
    Service service("Plumbing", "Pipe repair", 2.0);
    RepairTask task("Fix pipe", &service, 2.0);
    
    TaskAssignment assignment(&master, &task, "2024-01-01");
    EXPECT_NO_THROW(assignment.updateProgress("Work in progress"));
}

TEST(TaskAssignmentTest, MarkAsCompleted) {
    Plumber master(1, "Mike Plumber", 40000.0);
    Service service("Plumbing", "Pipe repair", 2.0);
    RepairTask task("Fix pipe", &service, 2.0);
    
    TaskAssignment assignment(&master, &task, "2024-01-01");
    EXPECT_NO_THROW(assignment.markAsCompleted());
}
