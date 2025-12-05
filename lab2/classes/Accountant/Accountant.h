#ifndef ACCOUNTANT_H
#define ACCOUNTANT_H

#include "../Employee/Employee.h"
#include <vector>
#include "../FinancialReport/FinancialReport.h"

class AccountingDepartment;

class Accountant : public Employee {
private:
    std::vector<FinancialReport*> preparedReports;
    std::string certificationNumber;
    AccountingDepartment* department;

public:
    Accountant(int id, const std::string& name, double salary, 
               const std::string& certification, AccountingDepartment* dept);
    ~Accountant();
    
    void performWork() override;
    class Invoice* generateInvoice(class RepairOrder* order);
    void processPayment(class Invoice* invoice, class Payment* payment);
    void calculateTaxes(FinancialReport* report);
};

#endif
