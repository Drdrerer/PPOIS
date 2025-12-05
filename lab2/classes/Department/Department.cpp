#include "Department.h"

Department::Department(const std::string& name, double budget) 
    : departmentName(name), budget(budget), headOfDepartment(nullptr) {}

std::string Department::getDepartmentName() const {
    return departmentName;
}

double Department::getBudget() const {
    return budget;
}

void Department::setHeadOfDepartment(Employee* head) {
    headOfDepartment = head;
}
