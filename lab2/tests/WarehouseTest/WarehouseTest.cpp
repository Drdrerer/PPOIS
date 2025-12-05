#include <gtest/gtest.h>
#include "../../classes/Warehouse/Warehouse.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"
#include "../../classes/InventoryItem/InventoryItem.h"
#include "../../classes/Supplier/Supplier.h"
#include "../../classes/Delivery/Delivery.h"
#include <vector>
#include <memory>

class WarehouseTest : public ::testing::Test {
protected:
    void SetUp() override {
        warehouse.reset(new Warehouse("Test Warehouse", 500));
        category.reset(new MaterialCategory("Construction", "Building materials"));
    }
    
    std::unique_ptr<Warehouse> warehouse;
    std::unique_ptr<MaterialCategory> category;
};

TEST_F(WarehouseTest, ConstructorAndGetters) {
    EXPECT_EQ(warehouse->getLocation(), "Test Warehouse");
    EXPECT_EQ(warehouse->getCapacity(), 500);
}

TEST_F(WarehouseTest, CheckAvailabilityEmptyWarehouse) {
    Material material("Concrete", category.get(), "kg");
    EXPECT_FALSE(warehouse->checkAvailability(&material));
}

TEST_F(WarehouseTest, FindAlternativeMaterialEmpty) {
    Material material("Concrete", category.get(), "kg");
    EXPECT_EQ(warehouse->findAlternativeMaterial(&material), nullptr);
}

TEST_F(WarehouseTest, UpdateInventoryBasic) {
    Material material("Paint", category.get(), "liters");
    
    EXPECT_NO_THROW(warehouse->updateInventory(&material, 50));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, -20));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, -100));
}

TEST_F(WarehouseTest, ProcessDelivery) {
    Supplier supplier("Test Supplier", 5);
    Delivery delivery("2024-01-15", &supplier);
    
    EXPECT_NO_THROW(warehouse->processDelivery(&delivery));
}

TEST_F(WarehouseTest, MultipleMaterialsOperations) {
    MaterialCategory newCategory("Electrical", "Wiring materials");
    
    Material wire("Wire 2.5mm", &newCategory, "m");
    Material cable("Cable", &newCategory, "m");
    Material connectors("Connectors", &newCategory, "pieces");
    
    EXPECT_NO_THROW(warehouse->updateInventory(&wire, 100));
    EXPECT_NO_THROW(warehouse->updateInventory(&cable, 50));
    EXPECT_NO_THROW(warehouse->updateInventory(&connectors, 200));
}

TEST_F(WarehouseTest, NullSafety) {
    EXPECT_NO_THROW(warehouse->checkAvailability(nullptr));
    EXPECT_EQ(warehouse->findAlternativeMaterial(nullptr), nullptr);
    EXPECT_NO_THROW(warehouse->updateInventory(nullptr, 100));
}

TEST_F(WarehouseTest, ZeroQuantity) {
    Material material("Test", category.get(), "units");
    EXPECT_NO_THROW(warehouse->updateInventory(&material, 0));
}

TEST_F(WarehouseTest, SameCategoryMaterials) {
    MaterialCategory cat("Tools", "Hand tools");
    
    Material hammer("Hammer", &cat, "pcs");
    Material screwdriver("Screwdriver", &cat, "pcs");
    Material wrench("Wrench", &cat, "pcs");
    
    EXPECT_NO_THROW(warehouse->updateInventory(&hammer, 10));
    EXPECT_NO_THROW(warehouse->updateInventory(&screwdriver, 20));
    EXPECT_NO_THROW(warehouse->updateInventory(&wrench, 15));
}

TEST_F(WarehouseTest, LargeQuantities) {
    Material material("Bulk Item", category.get(), "kg");
    
    for (int i = 0; i < 5; i++) {
        EXPECT_NO_THROW(warehouse->updateInventory(&material, 1000));
    }
}

TEST_F(WarehouseTest, MixedOperations) {
    Material material("Mixed Ops", category.get(), "units");
    
    EXPECT_NO_THROW(warehouse->updateInventory(&material, 100));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, -30));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, 50));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, -70));
    EXPECT_NO_THROW(warehouse->updateInventory(&material, 25));
}

TEST_F(WarehouseTest, WarehouseLocationChange) {
    Warehouse newWarehouse("New Location", 750);
    EXPECT_EQ(newWarehouse.getLocation(), "New Location");
    EXPECT_EQ(newWarehouse.getCapacity(), 750);
}

TEST_F(WarehouseTest, DifferentCapacityWarehouses) {
    Warehouse small("Small", 100);
    Warehouse medium("Medium", 1000);
    Warehouse large("Large", 10000);
    
    EXPECT_EQ(small.getCapacity(), 100);
    EXPECT_EQ(medium.getCapacity(), 1000);
    EXPECT_EQ(large.getCapacity(), 10000);
}
