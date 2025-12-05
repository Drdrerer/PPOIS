#include "Address.h"

Address::Address(const std::string& city, const std::string& street, const std::string& building)
    : city(city), street(street), buildingNumber(building) {}

bool Address::validateAddress() const {
    return !city.empty() && !street.empty() && !buildingNumber.empty();
}

std::string Address::getCoordinates() const {
    return city + "_" + street + "_" + buildingNumber;
}

std::string Address::getFullAddress() const {
    return city + ", " + street + ", " + buildingNumber;
}

std::string Address::getCity() const {
    return city;
}

std::string Address::getStreet() const {
    return street;
}
