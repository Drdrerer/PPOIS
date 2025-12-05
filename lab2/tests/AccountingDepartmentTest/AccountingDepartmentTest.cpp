#include <gtest/gtest.h>
#include "../../classes/AccountingDepartment/AccountingDepartment.h"
#include "../../classes/Invoice/Invoice.h"
#include "../../classes/Payment/Payment.h"
#include "../../classes/FinancialReport/FinancialReport.h"

TEST(AccountingDepartmentTest, ConstructorAndGetters) {
    AccountingDepartment dept(50000.0);
    EXPECT_EQ(dept.getDepartmentName(), "Accounting Department");
    EXPECT_EQ(dept.getBudget(), 50000.0);
}

TEST(AccountingDepartmentTest, GenerateFinancialReport) {
    AccountingDepartment dept(50000.0);
    
    FinancialReport* report = dept.generateFinancialReport("2024-01-01", "2024-01-31");
    EXPECT_NE(report, nullptr);
    EXPECT_GE(report->getTotalRevenue(), 0.0);
    delete report;
}

TEST(AccountingDepartmentTest, ProcessPayment) {
    AccountingDepartment dept(50000.0);
    Invoice invoice("INV001", 1000.0, "2024-12-31");
    Payment payment("PAY001", 1000.0, "2024-01-15");
    
    EXPECT_NO_THROW(dept.processPayment(&invoice, &payment));
}

TEST(AccountingDepartmentTest, ForecastRevenue) {
    AccountingDepartment dept(50000.0);
    double forecast = dept.forecastRevenue(3);
    EXPECT_GE(forecast, 0.0);
}

TEST(AccountingDepartmentTest, PerformOperations) {
    AccountingDepartment dept(50000.0);
    EXPECT_NO_THROW(dept.performDepartmentOperations());
}
