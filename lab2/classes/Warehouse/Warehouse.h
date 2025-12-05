#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>

class InventoryItem;
class Material;
class Delivery;

class Warehouse {
private:
    std::string location;
    std::vector<InventoryItem*> inventory;
    int capacity;

public:
    Warehouse(const std::string& location, int capacity);
    ~Warehouse();
    
    bool checkAvailability(Material* material) const;
    Material* findAlternativeMaterial(Material* material) const;
    void updateInventory(Material* material, int quantityChange);
    void processDelivery(Delivery* delivery);
    std::string getLocation() const;
    int getCapacity() const;
};

#endif
