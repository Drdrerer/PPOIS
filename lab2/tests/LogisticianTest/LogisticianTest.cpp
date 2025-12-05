#include <gtest/gtest.h>
#include "../../classes/Logistician/Logistician.h"
#include "../../classes/LogisticsDepartment/LogisticsDepartment.h"

class LogisticianTest : public Logistician {
public:
    LogisticianTest(int id, const std::string& name, double salary, LogisticsDepartment* dept)
        : Logistician(id, name, salary, dept) {}
};

TEST(LogisticianTest, Constructor) {
    LogisticsDepartment dept(40000.0);
    LogisticianTest logistician(1, "Logistics Expert", 45000.0, &dept);
    EXPECT_EQ(logistician.getFullName(), "Logistics Expert");
}

TEST(LogisticianTest, PerformWork) {
    LogisticsDepartment dept(40000.0);
    LogisticianTest logistician(1, "Logistics Expert", 45000.0, &dept);
    EXPECT_NO_THROW(logistician.performWork());
}
