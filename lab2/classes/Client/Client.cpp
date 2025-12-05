#include <iostream>
#include "Client.h"
#include "../Review/Review.h"
#include "../RepairOrder/RepairOrder.h"

Client::Client(const std::string& name, const std::string& phone) 
    : fullName(name), phoneNumber(phone) {}

Client::~Client() {
    for (auto order : orderHistory) {
        delete order;
    }
}

void Client::leaveReview(RepairOrder* order, int rating, const std::string& comment) {
    if (rating >= 1 && rating <= 5) {
        Review* review = new Review(rating, comment, order);
        std::cout << "Client " << fullName << " left " << rating 
                  << " star review: " << comment << std::endl;
    }
}

void Client::updateContactInfo(const std::string& newPhone, const std::string& newEmail) {
    phoneNumber = newPhone;
    std::cout << "Updated contact info for " << fullName << std::endl;
}

std::string Client::getFullName() const {
    return fullName;
}

std::string Client::getPhoneNumber() const {
    return phoneNumber;
}
