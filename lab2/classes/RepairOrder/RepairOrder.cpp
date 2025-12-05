#include <iostream>
#include "RepairOrder.h"
#include <algorithm>
#include "../Client/Client.h"

RepairOrder::RepairOrder(int id, Client* cl) 
    : orderId(id), client(cl), status(OrderStatus::CREATED) {}

RepairOrder::~RepairOrder() {
    for (auto task : tasks) {
        delete task;
    }
}

void RepairOrder::addTask(RepairTask* task) {
    tasks.push_back(task);
    std::cout << "Added task to order #" << orderId << ": " << task->getDescription() << std::endl;
}

void RepairOrder::removeTask(RepairTask* task) {
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Removed task from order #" << orderId << std::endl;
    }
}

void RepairOrder::changeStatus(OrderStatus newStatus) {
    status = newStatus;
    std::cout << "Order #" << orderId << " status changed" << std::endl;
}

double RepairOrder::calculateTotalCost() const {
    double total = 0.0;
    for (auto task : tasks) {
        total += task->getEstimatedHours() * 50.0;
    }
    return total;
}

double RepairOrder::calculateActualDuration() const {
    double totalHours = 0.0;
    for (auto task : tasks) {
        totalHours += task->getEstimatedHours();
    }
    return totalHours;
}

int RepairOrder::getOrderId() const {
    return orderId;
}

OrderStatus RepairOrder::getStatus() const {
    return status;
}
