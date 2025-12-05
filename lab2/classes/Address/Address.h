#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string city;
    std::string street;
    std::string buildingNumber;

public:
    Address(const std::string& city, const std::string& street, const std::string& building);
    
    bool validateAddress() const;
    std::string getCoordinates() const;
    std::string getFullAddress() const;
    std::string getCity() const;
    std::string getStreet() const;
};

#endif
