#ifndef HRDEPARTMENT_H
#define HRDEPARTMENT_H

#include "../Department/Department.h"
#include <vector>
#include <map>
#include "../Employee/Employee.h"
#include "../Qualification/Qualification.h"
#include "../WorkSchedule/WorkSchedule.h"

class HRDepartment : public Department {
private:
    std::vector<Employee*> employees;
    std::map<Qualification, int> qualificationRequirements;
    std::vector<WorkSchedule*> schedules;

public:
    HRDepartment(double budget);
    ~HRDepartment();
    
    void performDepartmentOperations() override;
    void hireEmployee(Employee* employee);
    void dismissEmployee(Employee* employee);
    double calculateSalary(Employee* employee, int workedDays) const;
    void approveVacation(Employee* employee, const std::string& from, const std::string& to);
};

#endif
