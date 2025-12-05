#ifndef ACCOUNTINGDEPARTMENT_H
#define ACCOUNTINGDEPARTMENT_H

#include "../Department/Department.h"
#include <vector>
#include "../Invoice/Invoice.h"
#include "../FinancialReport/FinancialReport.h"
#include "../TaxReport/TaxReport.h"

class AccountingDepartment : public Department {
private:
    std::vector<Invoice*> unpaidInvoices;
    TaxReport* lastTaxReport;
    double currentBalance;

public:
    AccountingDepartment(double budget);
    ~AccountingDepartment();
    
    void performDepartmentOperations() override;
    FinancialReport* generateFinancialReport(const std::string& from, const std::string& to);
    void processPayment(Invoice* invoice, class Payment* payment);
    double forecastRevenue(int months) const;
};

#endif
