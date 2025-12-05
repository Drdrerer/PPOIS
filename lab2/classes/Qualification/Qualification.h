#ifndef QUALIFICATION_H
#define QUALIFICATION_H

#include <string>

class Qualification {
private:
    std::string name;
    int level;
    std::string description;

public:
    Qualification(const std::string& name, int level, const std::string& desc);
    
    bool requiresRenewal() const;
    std::string getExpirationDate() const;
    bool isValidForWork() const;
    std::string getName() const;
    int getLevel() const;
};

#endif
