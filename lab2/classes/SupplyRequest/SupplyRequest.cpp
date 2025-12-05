#include <iostream>
#include "SupplyRequest.h"
#include "../Manager/Manager.h"

SupplyRequest::SupplyRequest(Material* material, int quantity, Supplier* supplier)
    : requestedMaterial(material), quantity(quantity), preferredSupplier(supplier) {}

void SupplyRequest::approveRequest(class Manager* manager) {
    std::cout << "Request approved by " << manager->getFullName() << std::endl;
}

void SupplyRequest::rejectRequest(const std::string& reason) {
    std::cout << "Request rejected: " << reason << std::endl;
}

bool SupplyRequest::isUrgent() const {
    return quantity > 100;
}

Material* SupplyRequest::getRequestedMaterial() const {
    return requestedMaterial;
}

int SupplyRequest::getQuantity() const {
    return quantity;
}
