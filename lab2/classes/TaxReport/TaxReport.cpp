#include <iostream>
#include "TaxReport.h"

TaxReport::TaxReport(int year, int quarter, double amount)
    : reportYear(year), reportQuarter(quarter), taxAmount(amount) {}

void TaxReport::submitToTaxAuthority() {
    std::cout << "Tax report submitted" << std::endl;
}

bool TaxReport::validateTaxCalculation() const {
    return taxAmount >= 0;
}

int TaxReport::getReportYear() const {
    return reportYear;
}

int TaxReport::getReportQuarter() const {
    return reportQuarter;
}

double TaxReport::getTaxAmount() const {
    return taxAmount;
}
