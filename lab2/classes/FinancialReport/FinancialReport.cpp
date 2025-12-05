#include <iostream>
#include "FinancialReport.h"

FinancialReport::FinancialReport(const std::string& start, const std::string& end)
    : periodStart(start), periodEnd(end), totalRevenue(0.0) {}

FinancialReport::~FinancialReport() {
    for (auto payment : processedPayments) {
        delete payment;
    }
}

double FinancialReport::calculateProfit() const {
    return totalRevenue * 0.8;
}

void FinancialReport::analyzeExpensesByCategory() {
    std::cout << "Analyzing expenses..." << std::endl;
}

void FinancialReport::exportToExcel(const std::string& filePath) const {
    std::cout << "Exported report to " << filePath << std::endl;
}

double FinancialReport::getTotalRevenue() const {
    return totalRevenue;
}

void FinancialReport::setTotalRevenue(double revenue) {
    totalRevenue = revenue;
}
