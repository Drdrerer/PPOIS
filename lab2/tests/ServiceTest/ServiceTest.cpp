#include <gtest/gtest.h>
#include "../../classes/Service/Service.h"
#include "../../classes/RepairObject/RepairObject.h"
#include "../../classes/Address/Address.h"

TEST(ServiceTest, ConstructorAndGetters) {
    Service service("Painting", "Wall painting", 8.0);
    
    EXPECT_EQ(service.getServiceName(), "Painting");
    EXPECT_EQ(service.getDescription(), "Wall painting");
    EXPECT_EQ(service.getBaseHours(), 8.0);
}

TEST(ServiceTest, EstimateCompletionTime) {
    Service service("Painting", "Wall painting", 8.0);
    
    double time = service.estimateCompletionTime();
    EXPECT_EQ(time, 8.0);
}

TEST(ServiceTest, ValidateCompatibility) {
    Service service("Painting", "Wall painting", 8.0);
    Address* address1 = new Address("City", "Street", "123");
    Address* address2 = new Address("City", "Street", "123");
    RepairObject validObject(address1, 100.0, "Apartment");
    RepairObject invalidObject(address2, 0.0, "Apartment");
    
    EXPECT_TRUE(service.validateCompatibilityWithObject(&validObject));
    EXPECT_FALSE(service.validateCompatibilityWithObject(&invalidObject));
}
