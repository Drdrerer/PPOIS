#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
class MaterialCategory;

class Material {
private:
    std::string name;
    MaterialCategory* category;
    std::string unitOfMeasure;

public:
    Material(const std::string& name, MaterialCategory* category, const std::string& unit);
    
    double calculateRequiredQuantity(double area) const;
    bool isCompatibleWith(Material* other) const;
    std::string getName() const;
    std::string getUnitOfMeasure() const;
    MaterialCategory* getCategory() const;
};

#endif
