#include <algorithm>
#include "AccountingDepartment.h"

AccountingDepartment::AccountingDepartment(double budget) 
    : Department("Accounting Department", budget), currentBalance(0.0), lastTaxReport(nullptr) {}

AccountingDepartment::~AccountingDepartment() {
    delete lastTaxReport;
}

void AccountingDepartment::performDepartmentOperations() {
    for (auto invoice : unpaidInvoices) {
        if (invoice->isOverdue()) {
            invoice->applyPenaltyForLatePayment();
        }
    }
}

FinancialReport* AccountingDepartment::generateFinancialReport(const std::string& from, const std::string& to) {
    FinancialReport* report = new FinancialReport(from, to);
    double total = 0.0;
    for (auto invoice : unpaidInvoices) {
        total += invoice->getTotalAmount();
    }
    report->setTotalRevenue(total);
    return report;
}

void AccountingDepartment::processPayment(Invoice* invoice, class Payment* payment) {
    if (payment->getAmount() >= invoice->getTotalAmount()) {
        auto it = std::find(unpaidInvoices.begin(), unpaidInvoices.end(), invoice);
        if (it != unpaidInvoices.end()) {
            unpaidInvoices.erase(it);
            currentBalance += payment->getAmount();
        }
    }
}

double AccountingDepartment::forecastRevenue(int months) const {
    return currentBalance * months * 1.1; 
}
