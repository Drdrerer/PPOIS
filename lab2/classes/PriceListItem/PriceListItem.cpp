#include "PriceListItem.h"

PriceListItem::PriceListItem(Service* service, double price, const std::string& currency)
    : service(service), price(price), currency(currency) {}

void PriceListItem::applyDiscount(double discountPercent) {
    price *= (1 - discountPercent / 100);
}

bool PriceListItem::isPriceValid() const {
    return price > 0;
}

Service* PriceListItem::getService() const {
    return service;
}

double PriceListItem::getPrice() const {
    return price;
}

std::string PriceListItem::getCurrency() const {
    return currency;
}
