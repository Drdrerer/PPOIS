#include "LegalEntityClient.h"

LegalEntityClient::LegalEntityClient(const std::string& company, const std::string& tax, 
                                   const std::string& address, const std::string& phone)
    : Client(company, phone), companyName(company), taxId(tax), legalAddress(address) {}

std::string LegalEntityClient::getClientType() const {
    return "Legal Entity";
}

bool LegalEntityClient::validateTaxInfo() const {
    return !taxId.empty() && taxId.length() >= 10;
}

std::string LegalEntityClient::getCompanyName() const {
    return companyName;
}

std::string LegalEntityClient::getTaxId() const {
    return taxId;
}
