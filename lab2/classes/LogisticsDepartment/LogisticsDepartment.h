#ifndef LOGISTICSDEPARTMENT_H
#define LOGISTICSDEPARTMENT_H

#include "../Department/Department.h"
#include <vector>
#include "../Supplier/Supplier.h"
#include "../Delivery/Delivery.h"

class Vehicle;

class LogisticsDepartment : public Department {
private:
    std::vector<Supplier*> approvedSuppliers;
    std::vector<Delivery*> expectedDeliveries;
    std::vector<Vehicle*> vehicles;

public:
    LogisticsDepartment(double budget);
    ~LogisticsDepartment();
    
    void performDepartmentOperations() override;
    Supplier* findOptimalSupplier(class Material* material) const;
    void addNewSupplier(Supplier* supplier);
    void planRouteForDelivery(Delivery* delivery);
};

#endif
