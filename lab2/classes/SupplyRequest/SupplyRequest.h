#ifndef SUPPLYREQUEST_H
#define SUPPLYREQUEST_H

#include "../Material/Material.h"
#include "../Supplier/Supplier.h"

class SupplyRequest {
private:
    Material* requestedMaterial;
    int quantity;
    Supplier* preferredSupplier;

public:
    SupplyRequest(Material* material, int quantity, Supplier* supplier);
    
    void approveRequest(class Manager* manager);
    void rejectRequest(const std::string& reason);
    bool isUrgent() const;
    Material* getRequestedMaterial() const;
    int getQuantity() const;
};

#endif
