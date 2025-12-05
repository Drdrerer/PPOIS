#include "TuringMachine.h"
#include <limits>

namespace turing_machine {

TuringMachine::TuringMachine(char blankSymbol) 
    : tape("", blankSymbol), currentState("q0"), initialState("q0"), 
      haltState("halt"), stepCount(0), maxSteps(100000) {}

TuringMachine::TuringMachine(const TuringMachine& other)
    : tape(other.tape), program(other.program), currentState(other.currentState),
      initialState(other.initialState), haltState(other.haltState),
      stepCount(other.stepCount), maxSteps(other.maxSteps) {}

TuringMachine& TuringMachine::operator=(const TuringMachine& other) {
    if (this != &other) {
        tape = other.tape;
        program = other.program;
        currentState = other.currentState;
        initialState = other.initialState;
        haltState = other.haltState;
        stepCount = other.stepCount;
        maxSteps = other.maxSteps;
    }
    return *this;
}

void TuringMachine::loadProgram(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string currentState, readSymbol, writeSymbol, moveDir, nextState;
        
        if (iss >> currentState >> readSymbol >> writeSymbol >> moveDir >> nextState) {
            if (readSymbol.length() == 1 && writeSymbol.length() == 1 && moveDir.length() == 1) {
                program.addRule(currentState, readSymbol[0], writeSymbol[0], 
                              moveDir[0], nextState);
            }
        }
    }
}

void TuringMachine::loadTape(std::istream& stream) {
    std::string tapeData;
    if (std::getline(stream, tapeData)) {
        tape = Tape(tapeData, tape.getBlankSymbol());
    }
}

void TuringMachine::loadFromFile(const std::string& filename) {
    loadConfiguration(*this, filename);
}

void TuringMachine::saveToFile(const std::string& filename) const {
    saveConfiguration(*this, filename);
}

bool TuringMachine::step() {
    if (stepCount >= maxSteps) {
        throw MaxStepsExceededException(maxSteps);
    }
    
    char currentSymbol = tape.read();
    Transition transition(' ', ' ', 'S', "");
    
    if (!program.getTransition(currentState, currentSymbol, transition)) {
        return false;
    }

    tape.write(transition.writeSymbol);
    tape.move(transition.moveDirection);
    currentState = transition.nextState;
    stepCount++;

    return currentState != haltState;
}

void TuringMachine::run(bool logging) {
    runWithCallback(logging);
}

void TuringMachine::runWithCallback(bool logging, std::function<void(const TuringMachine&)> callback) {
    stepCount = 0;
    
    if (logging) {
        printState();
    }
    if (callback) {
        callback(*this);
    }

    while (step()) {
        if (logging) {
            printState();
        }
        if (callback) {
            callback(*this);
        }
    }

    if (logging) {
        std::cout << "Final state:" << std::endl;
        printState();
    }
    if (callback) {
        callback(*this);
    }
}

void TuringMachine::printState(std::ostream& os) const {
    os << "Step " << stepCount << ": State=" << currentState 
       << ", Tape=" << tape.toString() 
       << ", Head at position " << tape.getPosition() << std::endl;
}

void TuringMachine::addRule(const std::string& currentState, char readSymbol, 
                           char writeSymbol, char moveDirection, const std::string& nextState) {
    program.addRule(currentState, readSymbol, writeSymbol, moveDirection, nextState);
}

void TuringMachine::removeRule(const std::string& currentState, char readSymbol) {
    program.removeRule(currentState, readSymbol);
}

void TuringMachine::printRules(std::ostream& os) const {
    os << "Program rules:" << std::endl;
    program.printAllRules(os);
}

void TuringMachine::setInitialState(const std::string& state) {
    initialState = state;
    currentState = state;
}

void TuringMachine::setHaltState(const std::string& state) {
    haltState = state;
}

void TuringMachine::reset() {
    tape.clear();
    currentState = initialState;
    stepCount = 0;
}

std::unique_ptr<TuringMachine> TuringMachine::createFromFile(const std::string& filename) {
    auto tm = std::make_unique<TuringMachine>();
    tm->loadFromFile(filename);
    return tm;
}

std::string TuringMachine::serialize() const {
    std::ostringstream oss;
    oss << currentState << "\n";
    oss << initialState << "\n";
    oss << haltState << "\n";
    oss << stepCount << "\n";
    oss << maxSteps << "\n";
    oss << tape.serialize() << "\n";
    oss << program.serialize();
    return oss.str();
}

void TuringMachine::deserialize(const std::string& data) {
    std::istringstream iss(data);
    
    std::getline(iss, currentState);
    std::getline(iss, initialState);
    std::getline(iss, haltState);
    
    iss >> stepCount;
    iss >> maxSteps;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string tapeData;
    std::getline(iss, tapeData);
    tape.deserialize(tapeData);
    
    std::stringstream programData;
    std::string line;
    while (std::getline(iss, line)) {
        programData << line << "\n";
    }
    program.deserialize(programData.str());
}

void loadConfiguration(TuringMachine& tm, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw InvalidConfigurationException("Cannot open file: " + filename);
    }

    std::string line;
    bool readingTape = false;
    bool readingProgram = false;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line == "[Tape]") {
            readingTape = true;
            readingProgram = false;
            continue;
        } else if (line == "[Program]") {
            readingTape = false;
            readingProgram = true;
            continue;
        } else if (line == "[Config]") {
            readingTape = false;
            readingProgram = false;
            continue;
        }

        if (readingTape) {
            tm.getTape() = Tape(line, tm.getTape().getBlankSymbol());
        } else if (readingProgram) {
            std::istringstream iss(line);
            std::string currentState, readSymbol, writeSymbol, moveDir, nextState;
            
            if (iss >> currentState >> readSymbol >> writeSymbol >> moveDir >> nextState) {
                if (readSymbol.length() == 1 && writeSymbol.length() == 1 && moveDir.length() == 1) {
                    tm.addRule(currentState, readSymbol[0], writeSymbol[0], 
                              moveDir[0], nextState);
                }
            }
        } else {
            std::istringstream iss(line);
            std::string key, value;
            if (iss >> key >> value) {
                if (key == "initialState:") {
                    tm.setInitialState(value);
                } else if (key == "haltState:") {
                    tm.setHaltState(value);
                } else if (key == "maxSteps:") {
                    tm.setMaxSteps(std::stoi(value));
                }
            }
        }
    }
}

void saveConfiguration(const TuringMachine& tm, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw InvalidConfigurationException("Cannot open file for writing: " + filename);
    }

    file << "[Config]" << std::endl;
    file << "initialState: " << tm.getInitialState() << std::endl;
    file << "haltState: " << tm.getHaltState() << std::endl;
    file << "maxSteps: " << tm.getMaxSteps() << std::endl;
    
    file << "[Tape]" << std::endl;
    file << "Initial tape data" << std::endl;
    
    file << "[Program]" << std::endl;
    tm.getProgram().saveStream(file);
}

}
