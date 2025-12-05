#include <algorithm>
#include "RepairFirm.h"

RepairFirm::RepairFirm(const std::string& name) : companyName(name), annualReport(nullptr) {}

RepairFirm::~RepairFirm() {
    for (auto dept : departments) {
        delete dept;
    }
    delete annualReport;
}

std::vector<Department*> RepairFirm::getActiveDepartments() const {
    std::vector<Department*> activeDepartments;
    for (auto dept : departments) {
        if (dept->getBudget() > 0) {
            activeDepartments.push_back(dept);
        }
    }
    return activeDepartments;
}

double RepairFirm::getMonthlyRevenue(int year, int month) const {
    double revenue = 0.0;
    for (auto dept : departments) {
        revenue += dept->getBudget() * 0.1;
    }
    return revenue;
}

double RepairFirm::calculateYearOverYearGrowth() const {
    if (annualReport == nullptr) return 0.0;
    double currentRevenue = annualReport->getTotalRevenue();
    return currentRevenue > 0 ? (currentRevenue * 0.15) : 0.0;
}

void RepairFirm::addDepartment(Department* department) {
    departments.push_back(department);
}

void RepairFirm::removeDepartment(Department* department) {
    auto it = std::find(departments.begin(), departments.end(), department);
    if (it != departments.end()) {
        departments.erase(it);
    }
}
