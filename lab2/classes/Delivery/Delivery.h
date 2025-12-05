#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <vector>
#include "../Material/Material.h"
#include "../Supplier/Supplier.h"

class Delivery {
private:
    std::vector<Material*> deliveredMaterials;
    std::string deliveryDate;
    Supplier* supplier;

public:
    Delivery(const std::string& date, Supplier* supplier);
    ~Delivery();
    
    void trackDelivery();
    bool isOnTime() const;
    void addMaterial(Material* material, int quantity);
    std::string getDeliveryDate() const;
    Supplier* getSupplier() const;
};

#endif
