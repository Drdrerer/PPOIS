#include <gtest/gtest.h>
#include "../../classes/Carpenter/Carpenter.h"

TEST(CarpenterTest, Constructor) {
    Carpenter carpenter(1, "Bob Carpenter", 38000.0, true);
    EXPECT_EQ(carpenter.getFullName(), "Bob Carpenter");
}

TEST(CarpenterTest, CarpentryMethods) {
    Carpenter carpenter(1, "Bob Carpenter", 38000.0, true);
    
    EXPECT_NO_THROW(carpenter.buildFurniture());
    EXPECT_NO_THROW(carpenter.installWoodenStructures());
    EXPECT_NO_THROW(carpenter.repairWoodwork());
}

TEST(CarpenterTest, PerformWork) {
    Carpenter carpenter(1, "Bob Carpenter", 38000.0, true);
    EXPECT_NO_THROW(carpenter.performWork());
}
