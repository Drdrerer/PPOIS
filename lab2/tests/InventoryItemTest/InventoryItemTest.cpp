#include <gtest/gtest.h>
#include "../../classes/InventoryItem/InventoryItem.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"

TEST(InventoryItemTest, ConstructorAndGetters) {
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    InventoryItem item(&material, 100, 10);
    
    EXPECT_EQ(item.getMaterial()->getName(), "Concrete");
    EXPECT_EQ(item.getQuantity(), 100);
    EXPECT_EQ(item.getMinStockLevel(), 10);
}

TEST(InventoryItemTest, NeedsRestocking) {
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    
    InventoryItem needsRestock(&material, 5, 10);
    InventoryItem sufficientStock(&material, 15, 10);
    
    EXPECT_TRUE(needsRestock.needsRestocking());
    EXPECT_FALSE(sufficientStock.needsRestocking());
}

TEST(InventoryItemTest, UpdateQuantity) {
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    InventoryItem item(&material, 100, 10);
    
    item.updateQuantity(150);
    EXPECT_EQ(item.getQuantity(), 150);
}
