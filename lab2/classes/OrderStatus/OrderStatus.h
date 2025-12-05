#ifndef ORDERSTATUS_H
#define ORDERSTATUS_H

#include <string>

class OrderStatus {
private:
    std::string statusName;
    std::string description;
    bool isFinal;

public:
    OrderStatus(const std::string& name, const std::string& desc, bool final);
    
    bool canTransitionTo(const OrderStatus& newStatus) const;
    std::string getStatusName() const;
    bool getIsFinal() const;
};

#endif
