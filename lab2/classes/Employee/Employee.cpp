#include "Employee.h"
#include <iostream>

Employee::Employee(int id, const std::string& name, double salary) 
    : employeeId(id), fullName(name), salary(salary) {}

void Employee::requestVacation(const std::string& from, const std::string& to) {
    std::cout << "Vacation request from " << fullName 
              << ": " << from << " to " << to << std::endl;
}

void Employee::updatePersonalInfo(const std::string& phone, const std::string& address) {
    std::cout << "Updating personal info for " << fullName << std::endl;
}

int Employee::getEmployeeId() const {
    return employeeId;
}

std::string Employee::getFullName() const {
    return fullName;
}

double Employee::getSalary() const {
    return salary;
}
