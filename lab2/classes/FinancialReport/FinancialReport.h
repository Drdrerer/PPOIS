#ifndef FINANCIALREPORT_H
#define FINANCIALREPORT_H

#include <string>
#include <vector>
#include "../Payment/Payment.h"

class FinancialReport {
private:
    std::string periodStart;
    std::string periodEnd;
    double totalRevenue;
    std::vector<Payment*> processedPayments;

public:
    FinancialReport(const std::string& start, const std::string& end);
    ~FinancialReport();
    
    double calculateProfit() const;
    void analyzeExpensesByCategory();
    void exportToExcel(const std::string& filePath) const;
    double getTotalRevenue() const;
    void setTotalRevenue(double revenue);
};

#endif
