#include <gtest/gtest.h>
#include "../../classes/LogisticsDepartment/LogisticsDepartment.h"
#include "../../classes/Supplier/Supplier.h"
#include "../../classes/Delivery/Delivery.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"

TEST(LogisticsDepartmentTest, ConstructorAndGetters) {
    LogisticsDepartment dept(40000.0);
    EXPECT_EQ(dept.getDepartmentName(), "Logistics Department");
}

TEST(LogisticsDepartmentTest, AddNewSupplier) {
    LogisticsDepartment dept(40000.0);
    Supplier* supplier = new Supplier("Test Supplier", 5);
    
    dept.addNewSupplier(supplier);
    delete supplier;
}

TEST(LogisticsDepartmentTest, FindOptimalSupplier) {
    LogisticsDepartment dept(40000.0);
    MaterialCategory category("Test", "Test");
    Material material("Test Material", &category, "kg");
    
    Supplier* supplier = dept.findOptimalSupplier(&material);
    EXPECT_EQ(supplier, nullptr);
}

TEST(LogisticsDepartmentTest, PerformOperations) {
    LogisticsDepartment dept(40000.0);
    EXPECT_NO_THROW(dept.performDepartmentOperations());
}
