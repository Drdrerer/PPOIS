#include <gtest/gtest.h>
#include "../../classes/LegalEntityClient/LegalEntityClient.h"

TEST(LegalEntityClientTest, ConstructorAndGetters) {
    LegalEntityClient client("Test Corp", "123-45-6789", "456 Business Ave", "555-0456");
    
    EXPECT_EQ(client.getClientType(), "Legal Entity");
    EXPECT_EQ(client.getCompanyName(), "Test Corp");
    EXPECT_EQ(client.getTaxId(), "123-45-6789");
}

TEST(LegalEntityClientTest, ValidateTaxInfo) {
    LegalEntityClient validClient("Test Corp", "123-45-6789", "456 Business Ave", "555-0456");
    LegalEntityClient invalidClient("Test Corp", "123", "456 Business Ave", "555-0456");
    
    EXPECT_TRUE(validClient.validateTaxInfo());
    EXPECT_FALSE(invalidClient.validateTaxInfo());
}
