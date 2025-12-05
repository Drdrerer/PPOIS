#include <iostream>
#include "ClientServiceDepartment.h"

ClientServiceDepartment::ClientServiceDepartment(double budget) 
    : Department("Client Service Department", budget) {}

ClientServiceDepartment::~ClientServiceDepartment() {
    for (auto review : publishedReviews) {
        delete review;
    }
}

void ClientServiceDepartment::performDepartmentOperations() {
    std::cout << "Processing " << complaintQueue.size() << " complaints" << std::endl;
}

void ClientServiceDepartment::registerComplaint(class RepairOrder* order, const std::string& complaintText) {
    std::cout << "Registered complaint for order #" << order->getOrderId() << std::endl;
}

void ClientServiceDepartment::processClientCall(Client* client, const std::string& inquiry) {
    std::cout << "Processing call from " << client->getFullName() << std::endl;
}

void ClientServiceDepartment::escalateComplaint(Complaint* complaint, class Manager* manager) {
    std::cout << "Complaint escalated to manager" << std::endl;
}
