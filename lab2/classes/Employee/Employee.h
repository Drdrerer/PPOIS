#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
protected:
    int employeeId;
    std::string fullName;
    double salary;

public:
    Employee(int id, const std::string& name, double salary);
    virtual ~Employee() = default;
    
    virtual void performWork() = 0;
    void requestVacation(const std::string& from, const std::string& to);
    void updatePersonalInfo(const std::string& phone, const std::string& address);
    int getEmployeeId() const;
    std::string getFullName() const;
    double getSalary() const;
};

#endif
