#include "RepairObject.h"


RepairObject::RepairObject(Address* addr, double area, const std::string& type)
    : address(addr), area(area), objectType(type) {}

RepairObject::~RepairObject() {
    delete address;
}

double RepairObject::calculateArea() const {
    return area;
}

int RepairObject::getObjectAge() const {
    return 5;
}

Address* RepairObject::getAddress() const {
    return address;
}

std::string RepairObject::getObjectType() const {
    return objectType;
}
