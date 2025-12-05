#include <iostream>
#include "Invoice.h"

Invoice::Invoice(const std::string& number, double amount, const std::string& due)
    : invoiceNumber(number), totalAmount(amount), dueDate(due) {}

void Invoice::applyPenaltyForLatePayment() {
    totalAmount *= 1.1;
    std::cout << "Applied late penalty to invoice " << invoiceNumber << std::endl;
}

void Invoice::extendDueDate(int additionalDays) {
    std::cout << "Extended due date for invoice " << invoiceNumber 
              << " by " << additionalDays << " days" << std::endl;
}

bool Invoice::isOverdue() const {
    return false;
}

std::string Invoice::getInvoiceNumber() const {
    return invoiceNumber;
}

double Invoice::getTotalAmount() const {
    return totalAmount;
}
