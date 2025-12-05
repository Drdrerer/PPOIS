#include <gtest/gtest.h>
#include "../../classes/WorkShift/WorkShift.h"

TEST(WorkShiftTest, ConstructorAndGetters) {
    WorkShift shift("09:00", "17:00");
    
    EXPECT_EQ(shift.getStartTime(), "09:00");
    EXPECT_EQ(shift.getEndTime(), "17:00");
}

TEST(WorkShiftTest, CalculateDuration) {
    WorkShift shift("09:00", "17:00");
    
    double duration = shift.calculateDuration();
    EXPECT_EQ(duration, 8.0);
}

TEST(WorkShiftTest, CheckOvertime) {
    WorkShift normal("09:00", "17:00");
    WorkShift overtime("09:00", "19:00");
    
    EXPECT_FALSE(normal.checkOvertime());
    EXPECT_FALSE(overtime.checkOvertime());
}
