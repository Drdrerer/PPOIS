#include <gtest/gtest.h>
#include "../../classes/Electrician/Electrician.h"

TEST(ElectricianTest, Constructor) {
    Electrician electrician(1, "John Electrician", 45000.0, 220);
    EXPECT_EQ(electrician.getFullName(), "John Electrician");
}

TEST(ElectricianTest, ElectricalMethods) {
    Electrician electrician(1, "John Electrician", 45000.0, 220);
    
    EXPECT_NO_THROW(electrician.installWiring());
    EXPECT_NO_THROW(electrician.repairCircuit());
    EXPECT_NO_THROW(electrician.checkElectricalSafety());
}

TEST(ElectricianTest, PerformWork) {
    Electrician electrician(1, "John Electrician", 45000.0, 220);
    EXPECT_NO_THROW(electrician.performWork());
}
