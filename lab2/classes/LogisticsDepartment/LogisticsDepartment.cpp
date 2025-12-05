#include <iostream>
#include "LogisticsDepartment.h"

LogisticsDepartment::LogisticsDepartment(double budget) 
    : Department("Logistics Department", budget) {}

LogisticsDepartment::~LogisticsDepartment() {
    for (auto vehicle : vehicles) {
        delete vehicle;
    }
}

void LogisticsDepartment::performDepartmentOperations() {
    std::cout << "Checking " << expectedDeliveries.size() << " expected deliveries" << std::endl;
}

Supplier* LogisticsDepartment::findOptimalSupplier(class Material* material) const {
    for (auto supplier : approvedSuppliers) {
        if (supplier->canSupply(material)) return supplier;
    }
    return nullptr;
}

void LogisticsDepartment::addNewSupplier(Supplier* supplier) {
    approvedSuppliers.push_back(supplier);
    std::cout << "Added supplier: " << supplier->getSupplierName() << std::endl;
}

void LogisticsDepartment::planRouteForDelivery(Delivery* delivery) {
    std::cout << "Route planned for " << delivery->getSupplier()->getSupplierName() << std::endl;
}
