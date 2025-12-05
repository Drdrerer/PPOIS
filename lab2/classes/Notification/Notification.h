#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
private:
    std::string message;
    std::string sentTime;
    std::string recipient;

public:
    Notification(const std::string& message, const std::string& time, const std::string& recipient);
    
    void sendSMS(const std::string& phoneNumber, const std::string& message);
    void sendEmail(const std::string& email, const std::string& subject, const std::string& body);
    bool isDelivered() const;
    std::string getMessage() const;
    std::string getRecipient() const;
};

#endif
