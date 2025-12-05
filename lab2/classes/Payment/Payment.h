#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class Payment {
private:
    std::string paymentId;
    double amount;
    std::string paymentDate;

public:
    Payment(const std::string& id, double amount, const std::string& date);
    
    bool validatePaymentDetails() const;
    void processRefund(double amount);
    std::string getPaymentId() const;
    double getAmount() const;
    std::string getPaymentDate() const;
};

#endif
