#include "Program.h"

namespace turing_machine {

void Program::addRule(const std::string& currentState, char readSymbol, 
                     char writeSymbol, char moveDirection, const std::string& nextState) {
    rules[currentState][readSymbol] = Transition(readSymbol, writeSymbol, moveDirection, nextState);
}

void Program::removeRule(const std::string& currentState, char readSymbol) {
    auto stateIt = rules.find(currentState);
    if (stateIt != rules.end()) {
        stateIt->second.erase(readSymbol);
        if (stateIt->second.empty()) {
            rules.erase(stateIt);
        }
    }
}

void Program::printRules(const std::string& state, std::ostream& os) const {
    auto stateIt = rules.find(state);
    if (stateIt != rules.end()) {
        for (const auto& transition : stateIt->second) {
            os << "  " << state << " " << transition.second.toString() << std::endl;
        }
    }
}

void Program::printAllRules(std::ostream& os) const {
    for (const auto& state : rules) {
        printRules(state.first, os);
    }
}

bool Program::getTransition(const std::string& currentState, char currentSymbol, 
                           Transition& transition) const {
    auto stateIt = rules.find(currentState);
    if (stateIt != rules.end()) {
        auto symbolIt = stateIt->second.find(currentSymbol);
        if (symbolIt != stateIt->second.end()) {
            transition = symbolIt->second;
            return true;
        }
    }
    return false;
}

bool Program::hasRules() const {
    return !rules.empty();
}

size_t Program::getRule() const {
    size_t count = 0;
    for (const auto& state : rules) {
        count += state.second.size();
    }
    return count;
}

bool Program::hasRule(const std::string& state, char symbol) const {
    auto stateIt = rules.find(state);
    if (stateIt != rules.end()) {
        return stateIt->second.find(symbol) != stateIt->second.end();
    }
    return false;
}

void Program::clear() {
    rules.clear();
}

std::vector<std::string> Program::getStates() const {
    std::vector<std::string> states;
    for (const auto& state : rules) {
        states.push_back(state.first);
    }
    return states;
}

std::string Program::serialize() const {
    std::ostringstream oss;
    saveStream(oss);
    return oss.str();
}

void Program::deserialize(const std::string& data) {
    std::istringstream iss(data);
    loadStream(iss);
}

void Program::saveStream(std::ostream& stream) const {
    stream << rules.size() << std::endl;
    for (const auto& state : rules) {
        stream << state.first << " " << state.second.size() << std::endl;
        for (const auto& transition : state.second) {
            stream << transition.first << " " << transition.second.toString() << std::endl;
        }
    }
}

void Program::loadStream(std::istream& stream) {
    rules.clear();
    size_t stateCount;
    stream >> stateCount;
    for (size_t i = 0; i < stateCount; ++i) {
        std::string stateName;
        size_t transitionCount;
        stream >> stateName >> transitionCount;
        for (size_t j = 0; j < transitionCount; ++j) {
            char readSymbol, writeSymbol, moveDirection;
            std::string nextState;
            stream >> readSymbol >> writeSymbol >> moveDirection >> nextState;
            rules[stateName][readSymbol] = Transition(readSymbol, writeSymbol, moveDirection, nextState);
        }
    }
}

}
