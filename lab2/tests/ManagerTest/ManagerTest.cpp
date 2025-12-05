#include <gtest/gtest.h>
#include "../../classes/Manager/Manager.h"
#include "../../classes/ClientServiceDepartment/ClientServiceDepartment.h"
#include "../../classes/PrivateClient/PrivateClient.h"
#include "../../classes/Address/Address.h"
#include "../../classes/RepairObject/RepairObject.h"

TEST(ManagerTest, ConstructorAndGetters) {
    ClientServiceDepartment csd(30000.0);
    Manager manager(1, "John Manager", 50000.0, &csd);
    
    EXPECT_EQ(manager.getEmployeeId(), 1);
    EXPECT_EQ(manager.getFullName(), "John Manager");
    EXPECT_EQ(manager.getSalary(), 50000.0);
}

TEST(ManagerTest, CreateOrder) {
    ClientServiceDepartment csd(30000.0);
    Manager manager(1, "John Manager", 50000.0, &csd);
    PrivateClient client("John Client", "AB123456", "123 Main St", "555-0123");
    Address* address = new Address("City", "Street", "123");
    RepairObject* object = new RepairObject(address, 100.0, "Apartment");
    
    RepairOrder* order = manager.createOrder(&client, object);
    EXPECT_NE(order, nullptr);
    EXPECT_EQ(order->getOrderId(), 1);
}

TEST(ManagerTest, CalculateInitialCost) {
    ClientServiceDepartment csd(30000.0);
    Manager manager(1, "John Manager", 50000.0, &csd);
    PrivateClient client("John Client", "AB123456", "123 Main St", "555-0123");
    Address* address = new Address("City", "Street", "123");
    RepairObject* object = new RepairObject(address, 100.0, "Apartment");
    
    RepairOrder* order = manager.createOrder(&client, object);
    double cost = manager.calculateInitialCost(order);
    EXPECT_GE(cost, 0.0);
}

TEST(ManagerTest, PerformWork) {
    ClientServiceDepartment csd(30000.0);
    Manager manager(1, "John Manager", 50000.0, &csd);
    EXPECT_NO_THROW(manager.performWork());
}
