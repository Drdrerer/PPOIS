#include <gtest/gtest.h>
#include "../../classes/Delivery/Delivery.h"
#include "../../classes/Supplier/Supplier.h"
#include "../../classes/MaterialCategory/MaterialCategory.h" 

TEST(DeliveryTest, ConstructorAndGetters) {
    Supplier supplier("BuildCorp", 5);
    Delivery delivery("2024-01-15", &supplier);
    
    EXPECT_EQ(delivery.getDeliveryDate(), "2024-01-15");
    EXPECT_NE(delivery.getSupplier(), nullptr);
}

TEST(DeliveryTest, TrackDelivery) {
    Supplier supplier("BuildCorp", 5);
    Delivery delivery("2024-01-15", &supplier);
    
    EXPECT_NO_THROW(delivery.trackDelivery());
}

TEST(DeliveryTest, AddMaterial) {
    Supplier supplier("BuildCorp", 5);
    Delivery delivery("2024-01-15", &supplier);
    
    MaterialCategory* category = new MaterialCategory("Test", "Test");
    Material* material = new Material("Test Material", category, "kg");
    
    EXPECT_NO_THROW(delivery.addMaterial(material, 100));
}
