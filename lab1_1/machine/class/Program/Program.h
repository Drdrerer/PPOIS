#ifndef TURING_MACHINE_PROGRAM_H
#define TURING_MACHINE_PROGRAM_H

#include "../Transition/Transition.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace turing_machine {

class Program {
private:
    std::unordered_map<std::string, std::unordered_map<char, Transition>> rules;

public:
    void addRule(const std::string& currentState, char readSymbol, 
                 char writeSymbol, char moveDirection, const std::string& nextState);
    void removeRule(const std::string& currentState, char readSymbol);
    void printRules(const std::string& state, std::ostream& os = std::cout) const;
    void printAllRules(std::ostream& os = std::cout) const;
    bool getTransition(const std::string& currentState, char currentSymbol, 
                       Transition& transition) const;
    bool hasRules() const;
    size_t getRule() const;
    bool hasRule(const std::string& state, char symbol) const;
    void clear();
    std::vector<std::string> getStates() const;
    
    std::string serialize() const;
    void deserialize(const std::string& data);
    void saveStream(std::ostream& stream) const;
    void loadStream(std::istream& stream);
};

}
#endif
