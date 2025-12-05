#include <gtest/gtest.h>
#include "../../classes/HRDepartment/HRDepartment.h"
#include "../../classes/Manager/Manager.h"
#include "../../classes/ClientServiceDepartment/ClientServiceDepartment.h"

TEST(HRDepartmentTest, ConstructorAndGetters) {
    HRDepartment hr(50000.0);
    EXPECT_EQ(hr.getDepartmentName(), "HR Department");
    EXPECT_EQ(hr.getBudget(), 50000.0);
}

TEST(HRDepartmentTest, HireEmployee) {
    HRDepartment hr(50000.0);
    ClientServiceDepartment csd(30000.0);
    Manager* manager = new Manager(1, "John Manager", 50000.0, &csd);
    
    hr.hireEmployee(manager);
}

TEST(HRDepartmentTest, DismissEmployee) {
    HRDepartment hr(50000.0);
    ClientServiceDepartment csd(30000.0);
    Manager* manager = new Manager(1, "John Manager", 50000.0, &csd);
    
    hr.hireEmployee(manager);
    hr.dismissEmployee(manager);
}

TEST(HRDepartmentTest, CalculateSalary) {
    HRDepartment hr(50000.0);
    ClientServiceDepartment csd(30000.0);
    Manager* manager = new Manager(1, "John Manager", 50000.0, &csd);
    
    double salary = hr.calculateSalary(manager, 22);
    EXPECT_GT(salary, 0.0);
}

TEST(HRDepartmentTest, PerformDepartmentOperations) {
    HRDepartment hr(50000.0);
    EXPECT_NO_THROW(hr.performDepartmentOperations());
}
