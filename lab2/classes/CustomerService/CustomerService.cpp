#include <iostream>
#include "CustomerService.h"

CustomerService::CustomerService(int id, const std::string& name, double salary, ClientServiceDepartment* dept)
    : Employee(id, name, salary), department(dept), resolvedTicketsCount(0) {}

void CustomerService::performWork() {
    std::cout << "CustomerService handling " << assignedClients.size() << " clients" << std::endl;
}

void CustomerService::handleClientInquiry(Client* client, const std::string& inquiry) {
    std::cout << "Handling inquiry from " << client->getFullName() << std::endl;
    resolvedTicketsCount++;
}

void CustomerService::resolveComplaint(class Complaint* complaint) {
    std::cout << "Complaint resolved" << std::endl;
    resolvedTicketsCount++;
}

void CustomerService::updateClientInfo(Client* client, const std::string& newInfo) {
    std::cout << "Updated info for " << client->getFullName() << std::endl;
}
