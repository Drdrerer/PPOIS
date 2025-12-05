#ifndef WORKSHIFT_H
#define WORKSHIFT_H

#include <string>
#include <vector>
#include "../Master/Master.h"

class WorkShift {
private:
    std::string startTime;
    std::string endTime;
    std::vector<Master*> assignedMasters;

public:
    WorkShift(const std::string& start, const std::string& end);
    
    double calculateDuration() const;
    bool checkOvertime() const;
    void addAssignedMaster(Master* master);
    std::string getStartTime() const;
    std::string getEndTime() const;
};

#endif
