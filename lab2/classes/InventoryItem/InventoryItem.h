#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

class Material;

class InventoryItem {
private:
    Material* material;
    int quantity;
    int minStockLevel;

public:
    InventoryItem(Material* material, int quantity, int minStock);
    
    bool needsRestocking() const;
    void updateQuantity(int newQuantity);
    Material* getMaterial() const;
    int getQuantity() const;
    int getMinStockLevel() const;
};

#endif
