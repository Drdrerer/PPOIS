#ifndef MANAGER_H
#define MANAGER_H

#include "../Employee/Employee.h"
#include <vector>
#include "../RepairOrder/RepairOrder.h"

class ClientServiceDepartment;

class Manager : public Employee {
private:
    std::vector<RepairOrder*> managedOrders;
    double bonus;
    ClientServiceDepartment* department;

public:
    Manager(int id, const std::string& name, double salary, ClientServiceDepartment* dept);
    
    void performWork() override;
    RepairOrder* createOrder(class Client* client, class RepairObject* object);
    double calculateInitialCost(RepairOrder* order) const;
    void assignTeamToOrder(RepairOrder* order, class Team* team);
    void sendNotificationToClient(class Client* client, class Notification* notification);
};

#endif
