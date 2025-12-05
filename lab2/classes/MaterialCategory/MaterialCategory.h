#ifndef MATERIALCATEGORY_H
#define MATERIALCATEGORY_H

#include <string>
#include <vector>

class Material;

class MaterialCategory {
private:
    std::string categoryName;
    std::string description;
    std::vector<Material*> materials;

public:
    MaterialCategory(const std::string& name, const std::string& desc);
    ~MaterialCategory();
    
    double getTotalCategoryValue() const;
    void addMaterial(Material* material);
    void removeMaterial(Material* material);
    std::string getCategoryName() const;
    std::string getDescription() const { return description; }
};

#endif
