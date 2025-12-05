#include <gtest/gtest.h>
#include "../../classes/RepairObject/RepairObject.h"
#include "../../classes/Address/Address.h"

TEST(RepairObjectTest, ConstructorAndGetters) {
    Address* address = new Address("New York", "Main St", "123");
    RepairObject object(address, 150.5, "Apartment");
    
    EXPECT_EQ(object.getObjectType(), "Apartment");
    EXPECT_EQ(object.calculateArea(), 150.5);
    EXPECT_NE(object.getAddress(), nullptr);
}

TEST(RepairObjectTest, GetObjectAge) {
    Address* address = new Address("City", "Street", "123");
    RepairObject object(address, 100.0, "House");
    
    int age = object.getObjectAge();
    EXPECT_GE(age, 0);
}
