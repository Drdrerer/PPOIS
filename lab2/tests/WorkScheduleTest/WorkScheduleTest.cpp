#include <gtest/gtest.h>
#include "../../classes/WorkSchedule/WorkSchedule.h"
#include "../../classes/Team/Team.h"

TEST(WorkScheduleTest, ConstructorAndGetters) {
    Team team("Test Team");
    WorkSchedule schedule("2024-01-01", &team);
    
    EXPECT_EQ(schedule.getDate(), "2024-01-01");
    EXPECT_NE(schedule.getAssignedTeam(), nullptr);
}

TEST(WorkScheduleTest, OptimizeShifts) {
    Team team("Test Team");
    WorkSchedule schedule("2024-01-01", &team);
    
    EXPECT_NO_THROW(schedule.optimizeShiftDistribution());
}
