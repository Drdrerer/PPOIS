#include <gtest/gtest.h>
#include "../../classes/OrderStatus/OrderStatus.h"

TEST(OrderStatusTest, ConstructorAndGetters) {
    OrderStatus status("Completed", "Order is completed", true);
    
    EXPECT_EQ(status.getStatusName(), "Completed");
    EXPECT_TRUE(status.getIsFinal());
}

TEST(OrderStatusTest, CanTransitionTo) {
    OrderStatus finalStatus("Completed", "Order is completed", true);
    OrderStatus nonFinalStatus("In Progress", "Work in progress", false);
    
    EXPECT_FALSE(finalStatus.canTransitionTo(nonFinalStatus));
    EXPECT_TRUE(nonFinalStatus.canTransitionTo(finalStatus));
}
