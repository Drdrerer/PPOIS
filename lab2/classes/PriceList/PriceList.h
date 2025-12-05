#ifndef PRICELIST_H
#define PRICELIST_H

#include <string>
#include <vector>
#include "../PriceListItem/PriceListItem.h"

class PriceList {
private:
    std::string version;
    std::string validFrom;
    std::vector<PriceListItem*> items;

public:
    PriceList(const std::string& version, const std::string& validFrom);
    ~PriceList();
    
    void addService(class Service* service, double price);
    void updateServicePrice(class Service* service, double newPrice);
    PriceListItem* findServiceByName(const std::string& serviceName) const;
    std::string getVersion() const;
    std::string getValidFrom() const;
};

#endif
