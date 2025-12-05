#include <iostream>
#include "Notification.h"

Notification::Notification(const std::string& message, const std::string& time, const std::string& recipient)
    : message(message), sentTime(time), recipient(recipient) {}

void Notification::sendSMS(const std::string& phoneNumber, const std::string& message) {
    std::cout << "SMS sent to " << phoneNumber << std::endl;
}

void Notification::sendEmail(const std::string& email, const std::string& subject, const std::string& body) {
    std::cout << "Email sent to " << email << std::endl;
}

bool Notification::isDelivered() const {
    return !recipient.empty();
}

std::string Notification::getMessage() const {
    return message;
}

std::string Notification::getRecipient() const {
    return recipient;
}
