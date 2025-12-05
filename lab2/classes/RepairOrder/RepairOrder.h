#ifndef REPAIRORDER_H
#define REPAIRORDER_H

#include <vector>
#include "../RepairTask/RepairTask.h"

enum class OrderStatus { CREATED, IN_PROGRESS, COMPLETED, PAID, CANCELLED };

class Client;

class RepairOrder {
private:
    int orderId;
    Client* client;
    std::vector<RepairTask*> tasks;
    OrderStatus status;

public:
    RepairOrder(int id, Client* client);
    ~RepairOrder();
    
    void addTask(RepairTask* task);
    void removeTask(RepairTask* task);
    void changeStatus(OrderStatus newStatus);
    double calculateTotalCost() const;
    double calculateActualDuration() const;
    int getOrderId() const;
    OrderStatus getStatus() const;
};

#endif
