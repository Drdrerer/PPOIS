#include <gtest/gtest.h>
#include "../../classes/PriceListItem/PriceListItem.h"
#include "../../classes/Service/Service.h"

TEST(PriceListItemTest, ConstructorAndGetters) {
    Service service("Painting", "Wall painting", 8.0);
    PriceListItem item(&service, 500.0, "USD");
    
    EXPECT_EQ(item.getPrice(), 500.0);
    EXPECT_EQ(item.getCurrency(), "USD");
    EXPECT_NE(item.getService(), nullptr);
}

TEST(PriceListItemTest, ApplyDiscount) {
    Service service("Painting", "Wall painting", 8.0);
    PriceListItem item(&service, 500.0, "USD");
    
    item.applyDiscount(10.0); 
    EXPECT_LT(item.getPrice(), 500.0);
}

TEST(PriceListItemTest, IsPriceValid) {
    Service service("Painting", "Wall painting", 8.0);
    
    PriceListItem valid(&service, 500.0, "USD");
    PriceListItem invalid(&service, -100.0, "USD");
    
    EXPECT_TRUE(valid.isPriceValid());
    EXPECT_FALSE(invalid.isPriceValid());
}
