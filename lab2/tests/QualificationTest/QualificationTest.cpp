#include <gtest/gtest.h>
#include "../../classes/Qualification/Qualification.h"

TEST(QualificationTest, ConstructorAndGetters) {
    Qualification qual("Electrician", 3, "Certified electrician");
    
    EXPECT_EQ(qual.getName(), "Electrician");
    EXPECT_EQ(qual.getLevel(), 3);
}

TEST(QualificationTest, RequiresRenewal) {
    Qualification qual("Electrician", 3, "Certified electrician");
    bool requiresRenewal = qual.requiresRenewal();
}

TEST(QualificationTest, GetExpirationDate) {
    Qualification qual("Electrician", 3, "Certified electrician");
    std::string expiration = qual.getExpirationDate();
    EXPECT_FALSE(expiration.empty());
}

TEST(QualificationTest, IsValidForWork) {
    Qualification validQual("Electrician", 3, "Certified electrician");
    Qualification invalidQual("", 0, "");
    
    EXPECT_TRUE(validQual.isValidForWork());
    EXPECT_FALSE(invalidQual.isValidForWork());
}
