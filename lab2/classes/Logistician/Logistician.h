#ifndef LOGISTICIAN_H
#define LOGISTICIAN_H

#include "../Employee/Employee.h"
#include <vector>
#include "../Delivery/Delivery.h"

class LogisticsDepartment;
class Route;

class Logistician : public Employee {
private:
    std::vector<Delivery*> plannedDeliveries;
    std::vector<Route*> optimalRoutes;
    LogisticsDepartment* department;

public:
    Logistician(int id, const std::string& name, double salary, LogisticsDepartment* dept);
    ~Logistician();
    
    void performWork() override;
    void planDelivery(class SupplyRequest* request, class Supplier* supplier);
    void calculateOptimalRoute(Delivery* delivery);
    void updateDeliveryStatus(Delivery* delivery, const std::string& status);
};

#endif
