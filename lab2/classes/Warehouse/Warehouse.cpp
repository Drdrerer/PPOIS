#include <iostream>
#include "Warehouse.h"
#include "../Material/Material.h"
#include "../Delivery/Delivery.h"
#include "../InventoryItem/InventoryItem.h"
#include <algorithm>

Warehouse::Warehouse(const std::string& location, int capacity)
    : location(location), capacity(capacity) {}

Warehouse::~Warehouse() {
    for (auto item : inventory) {
        delete item;
    }
}

bool Warehouse::checkAvailability(class Material* material) const {
    for (auto item : inventory) {
        if (item->getMaterial() == material && item->getQuantity() > 0) {
            return true;
        }
    }
    return false;
}

class Material* Warehouse::findAlternativeMaterial(class Material* material) const {
    for (auto item : inventory) {
        if (item->getMaterial()->getCategory() == material->getCategory() && 
            item->getQuantity() > 0) {
            return item->getMaterial();
        }
    }
    return nullptr;
}

void Warehouse::updateInventory(class Material* material, int quantityChange) {
    for (auto item : inventory) {
        if (item->getMaterial() == material) {
            int newQuantity = item->getQuantity() + quantityChange;
            if (newQuantity >= 0) {
                item->updateQuantity(newQuantity);
            }
            break;
        }
    }
}

void Warehouse::processDelivery(class Delivery* delivery) {
    std::cout << "Processing delivery from " << delivery->getSupplier()->getSupplierName() << std::endl;
}

std::string Warehouse::getLocation() const {
    return location;
}

int Warehouse::getCapacity() const {
    return capacity;
}
