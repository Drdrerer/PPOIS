#include "PrivateClient.h"

PrivateClient::PrivateClient(const std::string& name, const std::string& passport, 
                           const std::string& address, const std::string& phone, bool vip)
    : Client(name, phone), passportNumber(passport), homeAddress(address), isVIP(vip) {}

std::string PrivateClient::getClientType() const {
    return "Private";
}

bool PrivateClient::checkCreditHistory() const {
    return !passportNumber.empty() && passportNumber.length() >= 6;
}

std::string PrivateClient::getPassportNumber() const {
    return passportNumber;
}

bool PrivateClient::getVIPStatus() const {
    return isVIP;
}
