#include "Accountant.h"
#include "../AccountingDepartment/AccountingDepartment.h"
#include "../Invoice/Invoice.h"
#include "../FinancialReport/FinancialReport.h"
#include "../RepairOrder/RepairOrder.h"
#include <iostream>

Accountant::Accountant(int id, const std::string& name, double salary, 
                       const std::string& certification, AccountingDepartment* dept)
    : Employee(id, name, salary), certificationNumber(certification), department(dept) {}

Accountant::~Accountant() {
    for (auto report : preparedReports) {
        delete report;
    }
}

void Accountant::performWork() {
    std::cout << "Accountant " << getFullName() << " is working on financial reports" << std::endl;
}

class Invoice* Accountant::generateInvoice(class RepairOrder* order) {
    double amount = order->calculateTotalCost();
    std::string invoiceNumber = "INV_" + std::to_string(order->getOrderId());
    Invoice* invoice = new Invoice(invoiceNumber, amount, "2024-12-31");
    std::cout << "Generated invoice " << invoiceNumber << " for amount: " << amount << std::endl;
    return invoice;
}

void Accountant::processPayment(class Invoice* invoice, class Payment* payment) {
    if (payment->validatePaymentDetails()) {
        department->processPayment(invoice, payment);
        std::cout << "Processed payment for invoice " << invoice->getInvoiceNumber() << std::endl;
    }
}

void Accountant::calculateTaxes(FinancialReport* report) {
    double tax = report->getTotalRevenue() * 0.2;
    std::cout << "Calculated taxes: " << tax << std::endl;
}
