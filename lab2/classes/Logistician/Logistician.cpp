#include <iostream>
#include "Logistician.h"

Logistician::Logistician(int id, const std::string& name, double salary, LogisticsDepartment* dept)
    : Employee(id, name, salary), department(dept) {}

Logistician::~Logistician() {
    for (auto route : optimalRoutes) {
        delete route;
    }
}

void Logistician::performWork() {
    std::cout << "Logistician planning " << plannedDeliveries.size() << " deliveries" << std::endl;
}

void Logistician::planDelivery(class SupplyRequest* request, class Supplier* supplier) {
    plannedDeliveries.push_back(new Delivery("2024-12-31", supplier));
    std::cout << "Delivery planned" << std::endl;
}

void Logistician::calculateOptimalRoute(Delivery* delivery) {
    std::cout << "Calculating optimal route" << std::endl;
}

void Logistician::updateDeliveryStatus(Delivery* delivery, const std::string& status) {
    std::cout << "Delivery status updated to: " << status << std::endl;
}
