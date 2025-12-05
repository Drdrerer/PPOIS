#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class RepairObject;

class Service {
private:
    std::string serviceName;
    std::string description;
    double baseHours;

public:
    Service(const std::string& name, const std::string& desc, double hours);
    
    double estimateCompletionTime() const;
    bool validateCompatibilityWithObject(class RepairObject* object) const;
    std::string getServiceName() const;
    std::string getDescription() const;
    double getBaseHours() const;
};

#endif
