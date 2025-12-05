#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include "../Employee/Employee.h"
#include <vector>
#include "../Client/Client.h"

class ClientServiceDepartment;

class CustomerService : public Employee {
private:
    std::vector<Client*> assignedClients;
    int resolvedTicketsCount;
    ClientServiceDepartment* department;

public:
    CustomerService(int id, const std::string& name, double salary, ClientServiceDepartment* dept);
    
    void performWork() override;
    void handleClientInquiry(Client* client, const std::string& inquiry);
    void resolveComplaint(class Complaint* complaint);
    void updateClientInfo(Client* client, const std::string& newInfo);
};

#endif
