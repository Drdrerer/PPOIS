#ifndef PRIVATECLIENT_H
#define PRIVATECLIENT_H

#include "../Client/Client.h"
#include <string>

class PrivateClient : public Client {
private:
    std::string passportNumber;
    std::string homeAddress;
    bool isVIP;

public:
    PrivateClient(const std::string& name, const std::string& passport, 
                 const std::string& address, const std::string& phone, bool vip = false);
    
    std::string getClientType() const override;
    bool checkCreditHistory() const;
    std::string getPassportNumber() const;
    bool getVIPStatus() const;
};

#endif
