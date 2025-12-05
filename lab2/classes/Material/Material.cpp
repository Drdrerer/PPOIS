#include "Material.h"

Material::Material(const std::string& name, MaterialCategory* category, const std::string& unit)
    : name(name), category(category), unitOfMeasure(unit) {}

double Material::calculateRequiredQuantity(double area) const {
    return area * 0.1;
}

bool Material::isCompatibleWith(class Material* other) const {
    if (!other || !category) {
        return false;
    }
    return category == other->getCategory();
}

MaterialCategory* Material::getCategory() const {
    return category;
}

std::string Material::getName() const {
    return name;
}

std::string Material::getUnitOfMeasure() const {
    return unitOfMeasure;
}
