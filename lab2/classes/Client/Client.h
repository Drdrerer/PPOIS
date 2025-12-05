#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

class RepairOrder;

class Client {
protected:
    std::string fullName;
    std::vector<RepairOrder*> orderHistory;
    std::string phoneNumber;

public:
    Client(const std::string& name, const std::string& phone);
    virtual ~Client();
    
    virtual std::string getClientType() const = 0;
    void leaveReview(RepairOrder* order, int rating, const std::string& comment);
    void updateContactInfo(const std::string& newPhone, const std::string& newEmail);
    std::string getFullName() const;
    std::string getPhoneNumber() const;
};

#endif
