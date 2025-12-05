#include <iostream>
#include "Warehouseman.h"

#include "../Material/Material.h"
#include "../SupplyRequest/SupplyRequest.h" 
#include "../RepairTask/RepairTask.h"
#include "../Warehouse/Warehouse.h"        

Warehouseman::Warehouseman(int id, const std::string& name, double salary, Warehouse* warehouse)
    : Employee(id, name, salary), assignedWarehouse(warehouse), isInventoryAuditRequired(false) {}

Warehouseman::~Warehouseman() {
    for (auto request : processedRequests) {
        delete request;
    }
    processedRequests.clear();
}

void Warehouseman::performWork() {
    std::cout << "Warehouseman " << getFullName() << " checking inventory" << std::endl;
}

void Warehouseman::reserveMaterialsForTask(class RepairTask* task) {
    std::cout << "Reserving materials for task" << std::endl;
}

void Warehouseman::writeOffMaterial(class Material* material, double quantity) {
    std::cout << "Writing off " << quantity << " of " << material->getName() << std::endl;
}

void Warehouseman::conductInventoryAudit() {
    std::cout << "Conducting inventory audit" << std::endl;
    isInventoryAuditRequired = false;
}
