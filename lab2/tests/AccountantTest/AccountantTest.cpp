#include <gtest/gtest.h>
#include "../../classes/Accountant/Accountant.h"
#include "../../classes/AccountingDepartment/AccountingDepartment.h"
#include "../../classes/RepairOrder/RepairOrder.h"
#include "../../classes/PrivateClient/PrivateClient.h"
#include "../../classes/FinancialReport/FinancialReport.h"

class TestAccountant : public Accountant {
public:
    TestAccountant(int id, const std::string& name, double salary, 
                   const std::string& certification, AccountingDepartment* dept)
        : Accountant(id, name, salary, certification, dept) {}
};

TEST(AccountantTest, ConstructorAndGetters) {
    AccountingDepartment dept(50000.0);
    TestAccountant accountant(1, "John Accountant", 55000.0, "CPA123", &dept);
    
    EXPECT_EQ(accountant.getFullName(), "John Accountant");
    EXPECT_EQ(accountant.getEmployeeId(), 1);
}

TEST(AccountantTest, GenerateInvoice) {
    AccountingDepartment dept(50000.0);
    TestAccountant accountant(1, "John Accountant", 55000.0, "CPA123", &dept);
    PrivateClient client("Test Client", "AB123", "123 St", "555-0000");
    RepairOrder order(1, &client);
    
    Invoice* invoice = accountant.generateInvoice(&order);
    EXPECT_NE(invoice, nullptr);
    delete invoice;
}

TEST(AccountantTest, CalculateTaxes) {
    AccountingDepartment dept(50000.0);
    TestAccountant accountant(1, "John Accountant", 55000.0, "CPA123", &dept);
    FinancialReport report("2024-01-01", "2024-01-31");
    report.setTotalRevenue(100000.0);
    
    EXPECT_NO_THROW(accountant.calculateTaxes(&report));
}

TEST(AccountantTest, PerformWork) {
    AccountingDepartment dept(50000.0);
    TestAccountant accountant(1, "John Accountant", 55000.0, "CPA123", &dept);
    EXPECT_NO_THROW(accountant.performWork());
}
