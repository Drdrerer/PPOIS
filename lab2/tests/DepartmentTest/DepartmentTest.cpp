#include <gtest/gtest.h>
#include "../../classes/Department/Department.h"

class DepartmentTest : public Department {
public:
    DepartmentTest(const std::string& name, double budget) 
        : Department(name, budget) {}
    
    void performDepartmentOperations() override {
    }
};

TEST(DepartmentTest, ConstructorAndGetters) {
    DepartmentTest dept("Test Department", 30000.0);
    
    EXPECT_EQ(dept.getDepartmentName(), "Test Department");
    EXPECT_EQ(dept.getBudget(), 30000.0);
}

TEST(DepartmentTest, PerformOperations) {
    DepartmentTest dept("Test Department", 30000.0);
    EXPECT_NO_THROW(dept.performDepartmentOperations());
}
