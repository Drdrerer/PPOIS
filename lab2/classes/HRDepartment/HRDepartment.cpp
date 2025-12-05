#include <algorithm>
#include <iostream>
#include "HRDepartment.h"

HRDepartment::HRDepartment(double budget) 
    : Department("HR Department", budget) {}

HRDepartment::~HRDepartment() {
    for (auto schedule : schedules) {
        delete schedule;
    }
}

void HRDepartment::performDepartmentOperations() {
    for (auto& [qual, count] : qualificationRequirements) {
        int currentCount = 0;
        for (auto employee : employees) {
            currentCount++;
        }
        if (currentCount < count) {
        }
    }
}

void HRDepartment::hireEmployee(Employee* employee) {
    employees.push_back(employee);
    std::cout << "Hired employee: " << employee->getFullName() << std::endl;
}

void HRDepartment::dismissEmployee(Employee* employee) {
    auto it = std::find(employees.begin(), employees.end(), employee);
    if (it != employees.end()) {
        employees.erase(it);
        std::cout << "Dismissed employee: " << employee->getFullName() << std::endl;
    }
}

double HRDepartment::calculateSalary(Employee* employee, int workedDays) const {
    double baseSalary = employee->getSalary();
    return (baseSalary / 22) * workedDays;
}

void HRDepartment::approveVacation(Employee* employee, const std::string& from, const std::string& to) {
    std::cout << "Vacation approved for " << employee->getFullName() 
              << " from " << from << " to " << to << std::endl;
}
