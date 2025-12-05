#include <gtest/gtest.h>
#include "../../classes/ClientServiceDepartment/ClientServiceDepartment.h"
#include "../../classes/PrivateClient/PrivateClient.h"
#include "../../classes/RepairOrder/RepairOrder.h"

TEST(ClientServiceDepartmentTest, Constructor) {
    ClientServiceDepartment dept(30000.0);
    EXPECT_EQ(dept.getDepartmentName(), "Client Service Department");
}

TEST(ClientServiceDepartmentTest, PerformOperations) {
    ClientServiceDepartment dept(30000.0);
    EXPECT_NO_THROW(dept.performDepartmentOperations());
}
