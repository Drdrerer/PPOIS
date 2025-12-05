#ifndef TAXREPORT_H
#define TAXREPORT_H

#include <string>

class TaxReport {
private:
    int reportYear;
    int reportQuarter;
    double taxAmount;

public:
    TaxReport(int year, int quarter, double amount);
    
    void submitToTaxAuthority();
    bool validateTaxCalculation() const;
    int getReportYear() const;
    int getReportQuarter() const;
    double getTaxAmount() const;
};

#endif
