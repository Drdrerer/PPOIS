#include "Manager.h"
#include "../ClientServiceDepartment/ClientServiceDepartment.h"
#include "../Client/Client.h"
#include "../RepairOrder/RepairOrder.h"
#include "../Team/Team.h"
#include "../Notification/Notification.h"
#include <iostream>

Manager::Manager(int id, const std::string& name, double salary, ClientServiceDepartment* dept)
    : Employee(id, name, salary), department(dept), bonus(0.0) {}

void Manager::performWork() {
    std::cout << "Manager " << getFullName() << " is managing " 
              << managedOrders.size() << " orders" << std::endl;
}

RepairOrder* Manager::createOrder(Client* client, class RepairObject* object) {
    int newOrderId = managedOrders.empty() ? 1 : managedOrders.back()->getOrderId() + 1;
    RepairOrder* order = new RepairOrder(newOrderId, client);
    managedOrders.push_back(order);
    std::cout << "Created new order #" << newOrderId << " for client " 
              << client->getFullName() << std::endl;
    return order;
}

double Manager::calculateInitialCost(RepairOrder* order) const {
    double baseCost = order->calculateTotalCost();
    return baseCost * 1.2;
}

void Manager::assignTeamToOrder(RepairOrder* order, class Team* team) {
    std::cout << "Assigned team " << team->getTeamName() 
              << " to order #" << order->getOrderId() << std::endl;
}

void Manager::sendNotificationToClient(Client* client, class Notification* notification) {
    std::cout << "Sent notification to " << client->getFullName() 
              << ": " << notification->getMessage() << std::endl;
}
