#ifndef REPAIRFIRM_H
#define REPAIRFIRM_H

#include <string>
#include <vector>
#include "../FinancialReport/FinancialReport.h"
#include "../Department/Department.h"

class RepairFirm {
private:
    std::string companyName;
    std::vector<Department*> departments;
    FinancialReport* annualReport;

public:
    RepairFirm(const std::string& name);
    ~RepairFirm();
    
    std::vector<Department*> getActiveDepartments() const;
    double getMonthlyRevenue(int year, int month) const;
    double calculateYearOverYearGrowth() const;
    void addDepartment(Department* department);
    void removeDepartment(Department* department);
};

#endif
