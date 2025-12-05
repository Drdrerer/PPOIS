#include <gtest/gtest.h>
#include "../../classes/Notification/Notification.h"

TEST(NotificationTest, ConstructorAndGetters) {
    Notification notification("Test message", "2024-01-01 10:00", "john@email.com");
    
    EXPECT_EQ(notification.getMessage(), "Test message");
    EXPECT_EQ(notification.getRecipient(), "john@email.com");
}

TEST(NotificationTest, SendMethods) {
    Notification notification("Test", "2024-01-01", "test@email.com");
    
    EXPECT_NO_THROW(notification.sendSMS("555-0123", "Test SMS"));
    EXPECT_NO_THROW(notification.sendEmail("test@email.com", "Subject", "Body"));
}

TEST(NotificationTest, IsDelivered) {
    Notification delivered("Test", "2024-01-01", "recipient");
    Notification notDelivered("Test", "2024-01-01", "");
    
    EXPECT_TRUE(delivered.isDelivered());
    EXPECT_FALSE(notDelivered.isDelivered());
}
