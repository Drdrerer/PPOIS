#include <gtest/gtest.h>
#include "../../classes/Supplier/Supplier.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"

TEST(SupplierTest, ConstructorAndGetters) {
    Supplier supplier("BuildCorp", 5);
    
    EXPECT_EQ(supplier.getSupplierName(), "BuildCorp");
    EXPECT_EQ(supplier.getReliabilityRating(), 5);
}

TEST(SupplierTest, CanSupply) {
    Supplier supplier("BuildCorp", 5);
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    
    bool canSupply = supplier.canSupply(&material);
}

TEST(SupplierTest, UpdateRating) {
    Supplier supplier("BuildCorp", 5);
    supplier.updateReliabilityRating(4);
    EXPECT_EQ(supplier.getReliabilityRating(), 4);
}
