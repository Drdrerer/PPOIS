#include <gtest/gtest.h>
#include "../../classes/Tool/Tool.h"

TEST(ToolTest, ConstructorAndGetters) {
    Tool tool("Hammer", "Hand Tool", false);
    
    EXPECT_EQ(tool.getToolName(), "Hammer");
    EXPECT_EQ(tool.getToolType(), "Hand Tool");
}

TEST(ToolTest, Calibrate) {
    Tool tool("Drill", "Power Tool", true);
    EXPECT_NO_THROW(tool.calibrate());
}

TEST(ToolTest, CheckCalibration) {
    Tool calibrated("Hammer", "Hand Tool", false);
    Tool needsCalibration("Drill", "Power Tool", true);
    
    EXPECT_TRUE(calibrated.checkCalibrationStatus());
}
