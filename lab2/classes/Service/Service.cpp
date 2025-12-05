#include "Service.h"
#include "../RepairObject/RepairObject.h"

Service::Service(const std::string& name, const std::string& desc, double hours)
    : serviceName(name), description(desc), baseHours(hours) {}

double Service::estimateCompletionTime() const {
    return baseHours;
}

bool Service::validateCompatibilityWithObject(class RepairObject* object) const {
    return object->calculateArea() > 0;
}

std::string Service::getServiceName() const {
    return serviceName;
}

std::string Service::getDescription() const {
    return description;
}

double Service::getBaseHours() const {
    return baseHours;
}
