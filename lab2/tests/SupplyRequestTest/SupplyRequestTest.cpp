#include <gtest/gtest.h>
#include "../../classes/SupplyRequest/SupplyRequest.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"
#include "../../classes/Supplier/Supplier.h"

TEST(SupplyRequestTest, ConstructorAndGetters) {
    MaterialCategory category("Test", "Test");
    Material material("Test Material", &category, "kg");
    Supplier supplier("Test Supplier", 5);
    
    SupplyRequest request(&material, 100, &supplier);
    
    EXPECT_EQ(request.getQuantity(), 100);
    EXPECT_NE(request.getRequestedMaterial(), nullptr);
}

TEST(SupplyRequestTest, IsUrgent) {
    MaterialCategory category("Test", "Test");
    Material material("Test Material", &category, "kg");
    Supplier supplier("Test Supplier", 5);
    
    SupplyRequest urgent(&material, 150, &supplier);
    SupplyRequest normal(&material, 50, &supplier);
    
    EXPECT_TRUE(urgent.isUrgent());
    EXPECT_FALSE(normal.isUrgent());
}
