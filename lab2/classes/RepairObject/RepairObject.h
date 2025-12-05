#ifndef REPAIROBJECT_H
#define REPAIROBJECT_H

#include <string>
#include "../Address/Address.h"


class RepairObject {
private:
    Address* address;
    double area;
    std::string objectType;

public:
    RepairObject(Address* addr, double area, const std::string& type);
    ~RepairObject();
    
    double calculateArea() const;
    int getObjectAge() const;
    Address* getAddress() const;
    std::string getObjectType() const;
};

#endif
