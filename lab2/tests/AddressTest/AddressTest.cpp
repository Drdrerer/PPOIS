#include <gtest/gtest.h>
#include "../../classes/Address/Address.h"

TEST(AddressTest, ConstructorAndGetters) {
    Address address("New York", "Main Street", "123");
    
    EXPECT_EQ(address.getCity(), "New York");
    EXPECT_EQ(address.getStreet(), "Main Street");
    EXPECT_EQ(address.getFullAddress(), "New York, Main Street, 123");
}

TEST(AddressTest, ValidateAddress) {
    Address validAddress("New York", "Main Street", "123");
    Address invalidCity("", "Main Street", "123");
    Address invalidStreet("New York", "", "123");
    Address invalidBuilding("New York", "Main Street", "");
    
    EXPECT_TRUE(validAddress.validateAddress());
    EXPECT_FALSE(invalidCity.validateAddress());
    EXPECT_FALSE(invalidStreet.validateAddress());
    EXPECT_FALSE(invalidBuilding.validateAddress());
}

TEST(AddressTest, GetCoordinates) {
    Address address("New York", "Main Street", "123");
    std::string coordinates = address.getCoordinates();
    
    EXPECT_FALSE(coordinates.empty());
    EXPECT_NE(coordinates.find("New York"), std::string::npos);
}
