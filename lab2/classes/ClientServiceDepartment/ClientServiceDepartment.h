#ifndef CLIENTSERVICEDEPARTMENT_H
#define CLIENTSERVICEDEPARTMENT_H

#include "../Department/Department.h"
#include <vector>
#include <queue>
#include "../Client/Client.h"
#include "../Review/Review.h"

class Complaint;

class ClientServiceDepartment : public Department {
private:
    std::vector<Client*> clients;
    std::queue<Complaint*> complaintQueue;
    std::vector<Review*> publishedReviews;

public:
    ClientServiceDepartment(double budget);
    ~ClientServiceDepartment();
    
    void performDepartmentOperations() override;
    void registerComplaint(class RepairOrder* order, const std::string& complaintText);
    void processClientCall(Client* client, const std::string& inquiry);
    void escalateComplaint(Complaint* complaint, class Manager* manager);
};

#endif
