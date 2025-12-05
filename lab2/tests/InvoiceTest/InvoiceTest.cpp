#include <gtest/gtest.h>
#include "../../classes/Invoice/Invoice.h"

TEST(InvoiceTest, ConstructorAndGetters) {
    Invoice invoice("INV001", 1000.0, "2024-12-31");
    
    EXPECT_EQ(invoice.getInvoiceNumber(), "INV001");
    EXPECT_EQ(invoice.getTotalAmount(), 1000.0);
}

TEST(InvoiceTest, ApplyPenalty) {
    Invoice invoice("INV001", 1000.0, "2024-12-31");
    
    invoice.applyPenaltyForLatePayment();
}

TEST(InvoiceTest, ExtendDueDate) {
    Invoice invoice("INV001", 1000.0, "2024-12-31");
    EXPECT_NO_THROW(invoice.extendDueDate(7));
}

TEST(InvoiceTest, IsOverdue) {
    Invoice invoice("INV001", 1000.0, "2024-12-31");
    bool overdue = invoice.isOverdue();
    EXPECT_FALSE(overdue);
}
