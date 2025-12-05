#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <string>
#include <vector>
#include "../Material/Material.h"

class Supplier {
private:
    std::string supplierName;
    std::vector<Material*> suppliedMaterials;
    int reliabilityRating;

public:
    Supplier(const std::string& name, int rating);
    
    void supplyMaterials(const std::vector<Material*>& materials, int quantity);
    void updateReliabilityRating(int newRating);
    bool canSupply(Material* material) const;
    std::string getSupplierName() const;
    int getReliabilityRating() const;
};

#endif
