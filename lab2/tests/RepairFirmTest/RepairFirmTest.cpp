#include <gtest/gtest.h>
#include "../../classes/RepairFirm/RepairFirm.h"
#include "../../classes/HRDepartment/HRDepartment.h"

TEST(RepairFirmTest, ConstructorAndGetters) {
    RepairFirm firm("Test Firm");
    EXPECT_EQ(firm.getActiveDepartments().size(), 0);
}

TEST(RepairFirmTest, AddRemoveDepartment) {
    RepairFirm firm("Test Firm");
    HRDepartment* hr = new HRDepartment(50000.0);
    
    firm.addDepartment(hr);
    EXPECT_EQ(firm.getActiveDepartments().size(), 1);
    
    firm.removeDepartment(hr);
    EXPECT_EQ(firm.getActiveDepartments().size(), 0);
}

TEST(RepairFirmTest, MonthlyRevenueCalculation) {
    RepairFirm firm("Test Firm");
    HRDepartment* hr = new HRDepartment(50000.0);
    firm.addDepartment(hr);
    
    double revenue = firm.getMonthlyRevenue(2024, 1);
    EXPECT_GE(revenue, 0.0);
}

TEST(RepairFirmTest, YearOverYearGrowth) {
    RepairFirm firm("Test Firm");
    double growth = firm.calculateYearOverYearGrowth();
    EXPECT_GE(growth, 0.0);
}
