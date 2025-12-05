#include <iostream>
#include "Delivery.h"

Delivery::Delivery(const std::string& date, Supplier* supplier)
    : deliveryDate(date), supplier(supplier) {}

Delivery::~Delivery() {
    for (auto material : deliveredMaterials) {
        delete material;
    }
}

void Delivery::trackDelivery() {
    std::cout << "Tracking delivery from " << supplier->getSupplierName() << std::endl;
}

bool Delivery::isOnTime() const {
    return true;
}

void Delivery::addMaterial(Material* material, int quantity) {
    deliveredMaterials.push_back(material);
    std::cout << "Added " << material->getName() << " to delivery" << std::endl;
}

std::string Delivery::getDeliveryDate() const {
    return deliveryDate;
}

Supplier* Delivery::getSupplier() const {
    return supplier;
}
