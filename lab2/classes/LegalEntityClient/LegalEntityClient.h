#ifndef LEGALENTITYCLIENT_H
#define LEGALENTITYCLIENT_H

#include "../Client/Client.h"
#include <string>

class LegalEntityClient : public Client {
private:
    std::string companyName;
    std::string taxId;
    std::string legalAddress;

public:
    LegalEntityClient(const std::string& company, const std::string& tax, 
                     const std::string& address, const std::string& phone);
    
    std::string getClientType() const override;
    bool validateTaxInfo() const;
    std::string getCompanyName() const;
    std::string getTaxId() const;
};

#endif
