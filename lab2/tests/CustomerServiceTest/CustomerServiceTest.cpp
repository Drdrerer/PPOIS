#include <gtest/gtest.h>
#include "../../classes/CustomerService/CustomerService.h"
#include "../../classes/ClientServiceDepartment/ClientServiceDepartment.h"
#include "../../classes/PrivateClient/PrivateClient.h"

class CustomerServiceTest : public CustomerService {
public:
    CustomerServiceTest(int id, const std::string& name, double salary, ClientServiceDepartment* dept)
        : CustomerService(id, name, salary, dept) {}
};

TEST(CustomerServiceTest, Constructor) {
    ClientServiceDepartment dept(30000.0);
    CustomerServiceTest cs(1, "Support Agent", 30000.0, &dept);
    EXPECT_EQ(cs.getFullName(), "Support Agent");
}

TEST(CustomerServiceTest, HandleInquiry) {
    ClientServiceDepartment dept(30000.0);
    CustomerServiceTest cs(1, "Support Agent", 30000.0, &dept);
    PrivateClient client("Test Client", "AB123", "123 St", "555-0000");
    
    EXPECT_NO_THROW(cs.handleClientInquiry(&client, "Test inquiry"));
}
