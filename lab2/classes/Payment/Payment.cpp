#include <iostream>
#include "Payment.h"

Payment::Payment(const std::string& id, double amount, const std::string& date)
    : paymentId(id), amount(amount), paymentDate(date) {}

bool Payment::validatePaymentDetails() const {
    return !paymentId.empty() && amount > 0 && !paymentDate.empty();
}

void Payment::processRefund(double refundAmount) {
    std::cout << "Processing refund of " << refundAmount << std::endl;
}

std::string Payment::getPaymentId() const {
    return paymentId;
}

double Payment::getAmount() const {
    return amount;
}

std::string Payment::getPaymentDate() const {
    return paymentDate;
}
