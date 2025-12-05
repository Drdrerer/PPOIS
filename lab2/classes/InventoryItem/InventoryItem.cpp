#include <iostream>
#include "InventoryItem.h"
#include "../Material/Material.h"

InventoryItem::InventoryItem(Material* material, int quantity, int minStock)
    : material(material), quantity(quantity), minStockLevel(minStock) {}

bool InventoryItem::needsRestocking() const {
    return quantity <= minStockLevel;
}

void InventoryItem::updateQuantity(int newQuantity) {
    quantity = newQuantity;
    std::cout << "Updated quantity for " << material->getName() 
              << " to " << quantity << std::endl;
}

Material* InventoryItem::getMaterial() const {
    return material;
}

int InventoryItem::getQuantity() const {
    return quantity;
}

int InventoryItem::getMinStockLevel() const {
    return minStockLevel;
}
