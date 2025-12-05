#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include "../Employee/Employee.h"

class Department {
protected:
    std::string departmentName;
    Employee* headOfDepartment;
    double budget;

public:
    Department(const std::string& name, double budget);
    virtual ~Department() = default;
    
    virtual void performDepartmentOperations() = 0;
    std::string getDepartmentName() const;
    double getBudget() const;
    void setHeadOfDepartment(Employee* head);
};

#endif
