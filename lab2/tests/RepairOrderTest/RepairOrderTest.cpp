#include <gtest/gtest.h>
#include "../../classes/RepairOrder/RepairOrder.h"
#include "../../classes/PrivateClient/PrivateClient.h"
#include "../../classes/RepairTask/RepairTask.h"
#include "../../classes/Service/Service.h"

TEST(RepairOrderTest, ConstructorAndGetters) {
    PrivateClient client("John Client", "AB123456", "123 Main St", "555-0123");
    RepairOrder order(1, &client);
    
    EXPECT_EQ(order.getOrderId(), 1);
    EXPECT_EQ(order.getStatus(), OrderStatus::CREATED);
}

TEST(RepairOrderTest, AddRemoveTask) {
    PrivateClient client("John Client", "AB123456", "123 Main St", "555-0123");
    RepairOrder order(1, &client);
    Service service("Painting", "Wall painting", 8.0);
    RepairTask task("Paint living room", &service, 4.0);
    
    order.addTask(&task);
   
    order.removeTask(&task);
}

TEST(RepairOrderTest, ChangeStatus) {
    PrivateClient client("John Client", "AB123456", "123 Main St", "555-0123");
    RepairOrder order(1, &client);
    
    order.changeStatus(OrderStatus::IN_PROGRESS);
    EXPECT_EQ(order.getStatus(), OrderStatus::IN_PROGRESS);
}

TEST(RepairOrderTest, CalculateTotalCost) {
    PrivateClient* client = new PrivateClient("John Client", "AB123456", "123 Main St", "555-0123");
    RepairOrder order(1, client);
    Service service("Painting", "Wall painting", 8.0);
    RepairTask* task = new RepairTask("Paint living room", &service, 4.0);
    
    order.addTask(task);
    double cost = order.calculateTotalCost();
    EXPECT_GT(cost, 0.0);
}

TEST(RepairOrderTest, CalculateActualDuration) {
    PrivateClient* client = new PrivateClient("John Client", "AB123456", "123 Main St", "555-0123");
    RepairOrder order(1, client);
    Service service("Painting", "Wall painting", 8.0);
    RepairTask* task = new RepairTask("Paint living room", &service, 4.0);
    
    order.addTask(task);
    double duration = order.calculateActualDuration();
    EXPECT_GT(duration, 0.0);
}
