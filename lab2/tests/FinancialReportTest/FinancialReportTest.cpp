#include <gtest/gtest.h>
#include "../../classes/FinancialReport/FinancialReport.h"

TEST(FinancialReportTest, ConstructorAndGetters) {
    FinancialReport report("2024-01-01", "2024-01-31");
    
    EXPECT_EQ(report.getTotalRevenue(), 0.0);
    report.setTotalRevenue(100000.0);
    EXPECT_EQ(report.getTotalRevenue(), 100000.0);
}

TEST(FinancialReportTest, CalculateProfit) {
    FinancialReport report("2024-01-01", "2024-01-31");
    report.setTotalRevenue(100000.0);
    
    double profit = report.calculateProfit();
    EXPECT_GT(profit, 0.0);
    EXPECT_LT(profit, 100000.0);
}

TEST(FinancialReportTest, AnalyzeExpenses) {
    FinancialReport report("2024-01-01", "2024-01-31");
    EXPECT_NO_THROW(report.analyzeExpensesByCategory());
}

TEST(FinancialReportTest, ExportToExcel) {
    FinancialReport report("2024-01-01", "2024-01-31");
    EXPECT_NO_THROW(report.exportToExcel("test_report.xlsx"));
}
