#include <gtest/gtest.h>
#include "../../classes/Specialization/Specialization.h"
#include "../../classes/Qualification/Qualification.h"

TEST(SpecializationTest, ConstructorAndGetters) {
    Qualification qual("Electrician", 3, "Certified electrician");
    Specialization spec("Industrial Electrical", "Industrial", &qual);
    
    EXPECT_EQ(spec.getSpecializationName(), "Industrial Electrical");
    EXPECT_EQ(spec.getArea(), "Industrial");
}

TEST(SpecializationTest, MeetsRequirements) {
    Qualification requiredQual("Electrician", 3, "Certified");
    Qualification userQualLow("Electrician", 2, "Basic");
    Qualification userQualHigh("Electrician", 4, "Advanced");
    
    Specialization spec("Industrial Electrical", "Industrial", &requiredQual);
    
    EXPECT_FALSE(spec.meetsRequirements(&userQualLow));
    EXPECT_TRUE(spec.meetsRequirements(&userQualHigh));
}

TEST(SpecializationTest, AreaGetter) {
    Qualification qual("Plumber", 2, "Basic");
    Specialization spec("Residential Plumbing", "Residential", &qual);
    
    EXPECT_EQ(spec.getArea(), "Residential");
}
