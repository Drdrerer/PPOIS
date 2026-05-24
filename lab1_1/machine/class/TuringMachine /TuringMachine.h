#ifndef TURING_MACHINE_TURING_MACHINE_H
#define TURING_MACHINE_TURING_MACHINE_H

#include "../Tape/Tape.h"
#include "../Program/Program.h"
#include <memory>
#include <functional>
#include <fstream>
#include <stdexcept>

namespace turing_machine {

class TuringMachineException : public std::runtime_error {
public:
    explicit TuringMachineException(const std::string& message) 
        : std::runtime_error(message) {}
};

class MaxStepsExceededException : public TuringMachineException {
public:
    explicit MaxStepsExceededException(int steps)
        : TuringMachineException("Maximum steps exceeded: " + std::to_string(steps)) {}
};

class InvalidConfigurationException : public TuringMachineException {
public:
    explicit InvalidConfigurationException(const std::string& message)
        : TuringMachineException("Invalid configuration: " + message) {}
};

class TuringMachine {
private:
    Tape tape;
    Program program;
    std::string currentState;
    std::string initialState;
    std::string haltState;
    int stepCount;
    int maxSteps;

public:
    TuringMachine(char blankSymbol = 'B');
    TuringMachine(const TuringMachine& other);
    TuringMachine& operator=(const TuringMachine& other);
    
    void loadProgram(std::istream& stream);
    void loadTape(std::istream& stream);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    
    bool step();
    void run(bool logging = false);
    void runWithCallback(bool logging, std::function<void(const TuringMachine&)> callback = nullptr);
    
    void printState(std::ostream& os = std::cout) const;
    void addRule(const std::string& currentState, char readSymbol, 
                 char writeSymbol, char moveDirection, const std::string& nextState);
    void removeRule(const std::string& currentState, char readSymbol);
    void printRules(std::ostream& os = std::cout) const;
    
    void setInitialState(const std::string& state);
    void setHaltState(const std::string& state);
    void setMaxSteps(int max) { maxSteps = max; }
    void reset();

    Tape& getTape() { return tape; }
    const Tape& getTape() const { return tape; }
    const Program& getProgram() const { return program; }
    Program& getProgram() { return program; }
    std::string getCurrentState() const { return currentState; }
    std::string getInitialState() const { return initialState; }
    std::string getHaltState() const { return haltState; }
    int getStepCount() const { return stepCount; }
    int getMaxSteps() const { return maxSteps; }
    
    static std::unique_ptr<TuringMachine> createFromFile(const std::string& filename);
    
    std::string serialize() const;
    void deserialize(const std::string& data);
};

void loadConfiguration(TuringMachine& tm, const std::string& filename);
void saveConfiguration(const TuringMachine& tm, const std::string& filename);

}

#endif
