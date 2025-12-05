#include <gtest/gtest.h>
#include "../../classes/Roofer/Roofer.h"

TEST(RooferTest, Constructor) {
    Roofer roofer(1, "Tom Roofer", 42000.0, 10, true);
    EXPECT_EQ(roofer.getFullName(), "Tom Roofer");
}

TEST(RooferTest, RoofingMethods) {
    Roofer roofer(1, "Tom Roofer", 42000.0, 10, true);
    
    EXPECT_NO_THROW(roofer.installRoof());
    EXPECT_NO_THROW(roofer.repairLeaks());
    EXPECT_NO_THROW(roofer.checkRoofStructure());
}

TEST(RooferTest, PerformWork) {
    Roofer roofer(1, "Tom Roofer", 42000.0, 10, true);
    EXPECT_NO_THROW(roofer.performWork());
}
