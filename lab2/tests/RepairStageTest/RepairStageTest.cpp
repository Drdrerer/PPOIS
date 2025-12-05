#include <gtest/gtest.h>
#include "../../classes/RepairStage/RepairStage.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"

TEST(RepairStageTest, ConstructorAndGetters) {
    RepairStage stage("Preparation", 500.0);
    
    EXPECT_EQ(stage.getStageName(), "Preparation");
    EXPECT_EQ(stage.getStageCost(), 500.0);
}

TEST(RepairStageTest, AddUsedMaterial) {
    RepairStage stage("Test Stage", 100.0);
    
    MaterialCategory* category = new MaterialCategory("Test", "Test");
    Material* material = new Material("Test Material", category, "kg");
    
    EXPECT_NO_THROW(stage.addUsedMaterial(material, 10.0));
}

TEST(RepairStageTest, ValidateCompletion) {
    RepairStage stage("Test Stage", 100.0);
    bool completed = stage.validateStageCompletion();
}
