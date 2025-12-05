#include <gtest/gtest.h>
#include "../../classes/MaterialCategory/MaterialCategory.h"
#include "../../classes/Material/Material.h"

TEST(MaterialCategoryTest, ConstructorAndGetters) {
    MaterialCategory category("Construction", "Building materials");
    
    EXPECT_EQ(category.getCategoryName(), "Construction");
}

TEST(MaterialCategoryTest, AddRemoveMaterial) {
    MaterialCategory category("Construction", "Building materials");
    Material* material = new Material("Concrete", &category, "kg");
    
    EXPECT_NO_THROW(category.addMaterial(material));
    EXPECT_NO_THROW(category.removeMaterial(material));
}

TEST(MaterialCategoryTest, GetTotalValue) {
    MaterialCategory category("Construction", "Building materials");
    Material* material= new Material("Concrete", &category, "kg");
    category.addMaterial(material);
    
    double value = category.getTotalCategoryValue();
    EXPECT_GE(value, 0.0);
}
