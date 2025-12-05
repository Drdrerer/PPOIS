#include "Transition.h"

namespace turing_machine {

Transition::Transition(char read, char write, char move, const std::string& next)
    : readSymbol(read), writeSymbol(write), moveDirection(move), nextState(next) {}

bool Transition::operator==(const Transition& other) const {
    return readSymbol == other.readSymbol &&
           writeSymbol == other.writeSymbol &&
           moveDirection == other.moveDirection &&
           nextState == other.nextState;
}

std::string Transition::toString() const {
    std::ostringstream oss;
    oss << readSymbol << " " << writeSymbol << " " << moveDirection << " " << nextState;
    return oss.str();
}

}
