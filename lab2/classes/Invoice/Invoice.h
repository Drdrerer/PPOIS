#ifndef INVOICE_H
#define INVOICE_H

#include <string>

class Invoice {
private:
    std::string invoiceNumber;
    double totalAmount;
    std::string dueDate;

public:
    Invoice(const std::string& number, double amount, const std::string& due);
    
    void applyPenaltyForLatePayment();
    void extendDueDate(int additionalDays);
    bool isOverdue() const;
    std::string getInvoiceNumber() const;
    double getTotalAmount() const;
};

#endif
