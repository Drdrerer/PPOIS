#include <gtest/gtest.h>
#include "../../classes/Payment/Payment.h"

TEST(PaymentTest, ConstructorAndGetters) {
    Payment payment("PAY001", 1000.0, "2024-01-15");
    
    EXPECT_EQ(payment.getPaymentId(), "PAY001");
    EXPECT_EQ(payment.getAmount(), 1000.0);
    EXPECT_EQ(payment.getPaymentDate(), "2024-01-15");
}

TEST(PaymentTest, ValidatePaymentDetails) {
    Payment validPayment("PAY001", 1000.0, "2024-01-15");
    Payment invalidPayment("", 0.0, "");
    
    EXPECT_TRUE(validPayment.validatePaymentDetails());
    EXPECT_FALSE(invalidPayment.validatePaymentDetails());
}

TEST(PaymentTest, ProcessRefund) {
    Payment payment("PAY001", 1000.0, "2024-01-15");
    EXPECT_NO_THROW(payment.processRefund(500.0));
}
