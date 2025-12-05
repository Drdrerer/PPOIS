#include <gtest/gtest.h>
#include "../../classes/PrivateClient/PrivateClient.h"

TEST(PrivateClientTest, ConstructorAndGetters) {
    PrivateClient client("John Doe", "AB123456", "123 Main St", "555-0123", true);
    
    EXPECT_EQ(client.getClientType(), "Private");
    EXPECT_EQ(client.getPassportNumber(), "AB123456");
    EXPECT_TRUE(client.getVIPStatus());
}

TEST(PrivateClientTest, CheckCreditHistory) {
    PrivateClient validClient("John Doe", "AB123456", "123 Main St", "555-0123");
    PrivateClient invalidClient("Jane Doe", "AB12", "123 Main St", "555-0123");
    
    EXPECT_TRUE(validClient.checkCreditHistory());
    EXPECT_FALSE(invalidClient.checkCreditHistory());
}

TEST(PrivateClientTest, VIPStatus) {
    PrivateClient vipClient("VIP Client", "CD123456", "456 Oak St", "555-0456", true);
    PrivateClient regularClient("Regular Client", "EF123456", "789 Pine St", "555-0789", false);
    
    EXPECT_TRUE(vipClient.getVIPStatus());
    EXPECT_FALSE(regularClient.getVIPStatus());
}
