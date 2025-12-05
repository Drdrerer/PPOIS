#include <gtest/gtest.h>
#include "../../classes/Master/Master.h"

class MasterTest : public Master {
public:
    MasterTest(int id, const std::string& name, double salary)
        : Master(id, name, salary) {}
    
    void performRepairWork() override {
    }
};

TEST(MasterTest, ConstructorAndGetters) {
    MasterTest master(1, "John Master", 40000.0);
    EXPECT_EQ(master.getFullName(), "John Master");
    EXPECT_TRUE(master.getAvailability());
}

TEST(MasterTest, UpgradeQualification) {
    MasterTest master(1, "John Master", 40000.0);
    Qualification* qual = new Qualification("Advanced", 2, "Advanced level");
    
    EXPECT_NO_THROW(master.upgradeQualification(qual));
}

TEST(MasterTest, ReportMethods) {
    MasterTest master(1, "John Master", 40000.0);
    
    EXPECT_NO_THROW(master.reportTaskProgress(nullptr, 50));
    EXPECT_NO_THROW(master.reportWorkHours(nullptr, 8.0));
}
