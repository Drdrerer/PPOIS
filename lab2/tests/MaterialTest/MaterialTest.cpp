#include <gtest/gtest.h>
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"

TEST(MaterialTest, ConstructorAndGetters) {
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    
    EXPECT_EQ(material.getName(), "Concrete");
    EXPECT_EQ(material.getUnitOfMeasure(), "kg");
}

TEST(MaterialTest, CalculateRequiredQuantity) {
    MaterialCategory category("Construction", "Building materials");
    Material material("Concrete", &category, "kg");
    
    double quantity = material.calculateRequiredQuantity(100.0);
    EXPECT_GT(quantity, 0.0);
}

TEST(MaterialTest, IsCompatibleWith) {
    MaterialCategory category1("Construction", "Building materials");
    MaterialCategory category2("Electrical", "Electrical materials");
    
    Material material1("Concrete", &category1, "kg");
    Material material2("Bricks", &category1, "pcs");
    Material material3("Wire", &category2, "m");
    
    EXPECT_TRUE(material1.isCompatibleWith(&material2));
    EXPECT_FALSE(material1.isCompatibleWith(&material3));
}
