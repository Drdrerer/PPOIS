#include <iostream>
#include "MaterialCategory.h"

MaterialCategory::MaterialCategory(const std::string& name, const std::string& desc)
    : categoryName(name), description(desc) {}

MaterialCategory::~MaterialCategory() {
    for (auto material : materials) {
        delete material;
    }
}

double MaterialCategory::getTotalCategoryValue() const {
    double total = 0.0;
    for (auto material : materials) {
        total += 100.0;
    }
    return total;
}

void MaterialCategory::addMaterial(Material* material) {
    materials.push_back(material);
    std::cout << "Added material to category " << categoryName << std::endl;
}

void MaterialCategory::removeMaterial(Material* material) {
    std::cout << "Removed material from category" << std::endl;
}

std::string MaterialCategory::getCategoryName() const {
    return categoryName;
}
