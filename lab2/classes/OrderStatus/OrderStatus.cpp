#include "OrderStatus.h"

OrderStatus::OrderStatus(const std::string& name, const std::string& desc, bool final)
    : statusName(name), description(desc), isFinal(final) {}

bool OrderStatus::canTransitionTo(const OrderStatus& newStatus) const {
    return !isFinal;
}

std::string OrderStatus::getStatusName() const {
    return statusName;
}

bool OrderStatus::getIsFinal() const {
    return isFinal;
}
