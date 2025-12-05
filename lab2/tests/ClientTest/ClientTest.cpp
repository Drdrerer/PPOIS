#include <gtest/gtest.h>
#include "../../classes/Client/Client.h"
#include "../../classes/PrivateClient/PrivateClient.h"
#include "../../classes/RepairOrder/RepairOrder.h"

class ClientTest : public Client {
public:
    ClientTest(const std::string& name, const std::string& phone) 
        : Client(name, phone) {}
    
    std::string getClientType() const override {
        return "Test";
    }
};

TEST(ClientTest, ConstructorAndGetters) {
    ClientTest client("John Client", "555-0123");
    
    EXPECT_EQ(client.getFullName(), "John Client");
    EXPECT_EQ(client.getPhoneNumber(), "555-0123");
}

TEST(ClientTest, LeaveReview) {
    ClientTest client("John Client", "555-0123");
    PrivateClient orderClient("Order Client", "CD123456", "456 Oak St", "555-0456");
    RepairOrder order(1, &orderClient);
    
    EXPECT_NO_THROW(client.leaveReview(&order, 5, "Excellent service!"));
    EXPECT_NO_THROW(client.leaveReview(&order, 0, "Invalid rating")); // Должно обработать
}

TEST(ClientTest, UpdateContactInfo) {
    ClientTest client("John Client", "555-0123");
    EXPECT_NO_THROW(client.updateContactInfo("555-0789", "john@email.com"));
}
