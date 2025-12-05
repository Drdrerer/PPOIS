#ifndef PRICELISTITEM_H
#define PRICELISTITEM_H

#include "../Service/Service.h"
#include <string>

class PriceListItem {
private:
    Service* service;
    double price;
    std::string currency;

public:
    PriceListItem(Service* service, double price, const std::string& currency);
    
    void applyDiscount(double discountPercent);
    bool isPriceValid() const;
    Service* getService() const;
    double getPrice() const;
    std::string getCurrency() const;
};

#endif
