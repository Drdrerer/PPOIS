#ifndef TURING_MACHINE_TRANSITION_H
#define TURING_MACHINE_TRANSITION_H

#include <string>
#include <sstream>
#include <limits>

namespace turing_machine {

class Transition {
public:
    char readSymbol;
    char writeSymbol;
    char moveDirection;
    std::string nextState;

    Transition(char read = ' ', char write = ' ', char move = 'S', const std::string& next = "");
    bool operator==(const Transition& other) const;
    std::string toString() const;
};

}
#endif
