#include <gtest/gtest.h>
#include "../../classes/Warehouseman/Warehouseman.h"
#include "../../classes/Warehouse/Warehouse.h"
#include "../../classes/Material/Material.h"
#include "../../classes/MaterialCategory/MaterialCategory.h"
#include <memory>

class WarehousemanTest : public ::testing::Test {
protected:
    void SetUp() override {
        warehouse = std::make_shared<Warehouse>("Test Warehouse", 1000);
        category = std::make_shared<MaterialCategory>("Construction", "Building materials");
        material = std::make_shared<Material>("Concrete", category.get(), "kg");
    }
    
    std::shared_ptr<Warehouse> warehouse;
    std::shared_ptr<MaterialCategory> category;
    std::shared_ptr<Material> material;
};

TEST_F(WarehousemanTest, ConstructorAndBasicInfo) {
    Warehouseman worker(1, "John Doe", 35000.0, warehouse.get());
    
    EXPECT_EQ(worker.getFullName(), "John Doe");
}

TEST_F(WarehousemanTest, PerformWork) {
    Warehouseman worker(1, "John", 35000.0, warehouse.get());
    
    EXPECT_NO_THROW(worker.performWork());

    testing::internal::CaptureStdout();
    worker.performWork();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(WarehousemanTest, WriteOffMaterial) {
    Warehouseman worker(1, "John", 35000.0, warehouse.get());
    
    EXPECT_NO_THROW(worker.writeOffMaterial(material.get(), 5.0));
    
    testing::internal::CaptureStdout();
    worker.writeOffMaterial(material.get(), 5.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(WarehousemanTest, ConductInventoryAudit) {
    Warehouseman worker(1, "John", 35000.0, warehouse.get());
    
    EXPECT_NO_THROW(worker.conductInventoryAudit());
    
    testing::internal::CaptureStdout();
    worker.conductInventoryAudit();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(WarehousemanTest, ReserveMaterialsForTask) {
    Warehouseman worker(1, "John", 35000.0, warehouse.get());
    
    EXPECT_NO_THROW(worker.reserveMaterialsForTask(nullptr));
    
    testing::internal::CaptureStdout();
    worker.reserveMaterialsForTask(nullptr);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}
