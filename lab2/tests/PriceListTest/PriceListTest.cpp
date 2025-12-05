#include <gtest/gtest.h>
#include "../../classes/PriceList/PriceList.h"
#include "../../classes/Service/Service.h"

TEST(PriceListTest, ConstructorAndGetters) {
    PriceList priceList("v1.0", "2024-01-01");
    
    EXPECT_EQ(priceList.getVersion(), "v1.0");
    EXPECT_EQ(priceList.getValidFrom(), "2024-01-01");
}

TEST(PriceListTest, AddService) {
    PriceList priceList("v1.0", "2024-01-01");
    Service service("Painting", "Wall painting", 8.0);
    
    EXPECT_NO_THROW(priceList.addService(&service, 500.0));
}

TEST(PriceListTest, UpdateServicePrice) {
    PriceList priceList("v1.0", "2024-01-01");
    Service service("Painting", "Wall painting", 8.0);
    
    EXPECT_NO_THROW(priceList.updateServicePrice(&service, 550.0));
}
