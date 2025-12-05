#include <iostream>
#include "Supplier.h"

Supplier::Supplier(const std::string& name, int rating)
    : supplierName(name), reliabilityRating(rating) {}

void Supplier::supplyMaterials(const std::vector<Material*>& materials, int quantity) {
    std::cout << "Supplied " << materials.size() << " materials" << std::endl;
}

void Supplier::updateReliabilityRating(int newRating) {
    reliabilityRating = newRating;
}

bool Supplier::canSupply(Material* material) const {
    for (auto suppliedMaterial : suppliedMaterials) {
        if (suppliedMaterial == material) return true;
    }
    return false;
}

std::string Supplier::getSupplierName() const {
    return supplierName;
}

int Supplier::getReliabilityRating() const {
    return reliabilityRating;
}
