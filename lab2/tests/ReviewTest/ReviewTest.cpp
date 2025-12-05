#include <gtest/gtest.h>
#include "../../classes/Review/Review.h"
#include "../../classes/RepairOrder/RepairOrder.h"
#include "../../classes/PrivateClient/PrivateClient.h"

TEST(ReviewTest, ConstructorAndGetters) {
    PrivateClient client("Test", "AB123", "123 St", "555-0000");
    RepairOrder order(1, &client);
    Review review(5, "Excellent service!", &order);
    
    EXPECT_EQ(review.getRating(), 5);
    EXPECT_EQ(review.getComment(), "Excellent service!");
}

TEST(ReviewTest, ModerateReview) {
    PrivateClient client("Test", "AB123", "123 St", "555-0000");
    RepairOrder order(1, &client);
    
    Review valid(5, "Good", &order);
    Review invalidRating(0, "Bad", &order);
    
    EXPECT_TRUE(valid.moderateReview());
    EXPECT_FALSE(invalidRating.moderateReview());
}

TEST(ReviewTest, PublishReview) {
    PrivateClient client("Test", "AB123", "123 St", "555-0000");
    RepairOrder order(1, &client);
    Review review(5, "Excellent service!", &order);
    
    EXPECT_NO_THROW(review.publishReview());
}
