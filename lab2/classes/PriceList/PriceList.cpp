#include <iostream>
#include "PriceList.h"

PriceList::PriceList(const std::string& version, const std::string& validFrom)
    : version(version), validFrom(validFrom) {}

PriceList::~PriceList() {
    for (auto item : items) {
        delete item;
    }
}

void PriceList::addService(class Service* service, double price) {
    items.push_back(new PriceListItem(service, price, "USD"));
    std::cout << "Added service to price list" << std::endl;
}

void PriceList::updateServicePrice(class Service* service, double newPrice) {
    std::cout << "Updated price for service" << std::endl;
}

PriceListItem* PriceList::findServiceByName(const std::string& serviceName) const {
    for (auto item : items) {
    }
    return nullptr;
}

std::string PriceList::getVersion() const {
    return version;
}

std::string PriceList::getValidFrom() const {
    return validFrom;
}
