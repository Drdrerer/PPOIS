#ifndef WAREHOUSEMAN_H
#define WAREHOUSEMAN_H

#include "../Employee/Employee.h"
#include <vector>

class Warehouse;
class SupplyRequest;
class RepairTask;
class Material;

class Warehouseman : public Employee {
private:
    Warehouse* assignedWarehouse;
    std::vector<SupplyRequest*> processedRequests;
    bool isInventoryAuditRequired;

public:
    Warehouseman(int id, const std::string& name, double salary, Warehouse* warehouse);
    ~Warehouseman();
    
    void performWork() override;
    void reserveMaterialsForTask(RepairTask* task);
    void writeOffMaterial(Material* material, double quantity);
    void conductInventoryAudit();
};

#endif
