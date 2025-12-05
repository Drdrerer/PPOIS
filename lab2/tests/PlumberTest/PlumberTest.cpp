#include <gtest/gtest.h>
#include "../../classes/Plumber/Plumber.h"

TEST(PlumberTest, Constructor) {
    Plumber plumber(1, "Mike Plumber", 40000.0);
    EXPECT_EQ(plumber.getFullName(), "Mike Plumber");
}

TEST(PlumberTest, PlumbingMethods) {
    Plumber plumber(1, "Mike Plumber", 40000.0);
    
    EXPECT_NO_THROW(plumber.unclogPipe());
    EXPECT_NO_THROW(plumber.installPlumbingSystem());
    EXPECT_NO_THROW(plumber.repairFaucet());
}

TEST(PlumberTest, PerformWork) {
    Plumber plumber(1, "Mike Plumber", 40000.0);
    EXPECT_NO_THROW(plumber.performWork());
}
