#include <gtest/gtest.h>
#include "../../classes/TaxReport/TaxReport.h"

TEST(TaxReportTest, ConstructorAndGetters) {
    TaxReport report(2024, 1, 5000.0);
    
    EXPECT_EQ(report.getReportYear(), 2024);
    EXPECT_EQ(report.getReportQuarter(), 1);
    EXPECT_EQ(report.getTaxAmount(), 5000.0);
}

TEST(TaxReportTest, ValidateTaxCalculation) {
    TaxReport valid(2024, 1, 5000.0);
    TaxReport invalid(2024, 1, -100.0);
    
    EXPECT_TRUE(valid.validateTaxCalculation());
    EXPECT_FALSE(invalid.validateTaxCalculation());
}

TEST(TaxReportTest, SubmitToTaxAuthority) {
    TaxReport report(2024, 1, 5000.0);
    EXPECT_NO_THROW(report.submitToTaxAuthority());
}
