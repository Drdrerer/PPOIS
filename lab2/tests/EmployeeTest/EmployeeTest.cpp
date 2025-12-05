#include <gtest/gtest.h>
#include "../../classes/Employee/Employee.h"

class EmployeeTest : public Employee {
public:
    EmployeeTest(int id, const std::string& name, double salary) 
        : Employee(id, name, salary) {}
    
    void performWork() override {
    }
};

TEST(EmployeeTest, ConstructorAndGetters) {
    EmployeeTest employee(1, "John Doe", 50000.0);
    
    EXPECT_EQ(employee.getEmployeeId(), 1);
    EXPECT_EQ(employee.getFullName(), "John Doe");
    EXPECT_EQ(employee.getSalary(), 50000.0);
}

TEST(EmployeeTest, RequestVacation) {
    EmployeeTest employee(1, "John Doe", 50000.0);
    EXPECT_NO_THROW(employee.requestVacation("2024-01-01", "2024-01-14"));
}

TEST(EmployeeTest, UpdatePersonalInfo) {
    EmployeeTest employee(1, "John Doe", 50000.0);
    EXPECT_NO_THROW(employee.updatePersonalInfo("555-0123", "123 Main St"));
}

TEST(EmployeeTest, PerformWork) {
    EmployeeTest employee(1, "John Doe", 50000.0);
    EXPECT_NO_THROW(employee.performWork());
}
