#ifndef TURING_MACHINE_TAPE_H
#define TURING_MACHINE_TAPE_H

#include <unordered_map>
#include <string>
#include <utility>
#include <sstream>

namespace turing_machine {

class Tape {
private:
    std::unordered_map<int, char> cells;
    int headPosition;
    char blankSymbol;

public:
    Tape(const std::string& initialData = "", char blank = 'B');
    Tape(const Tape& other);
    Tape& operator=(const Tape& other);
    
    char read() const;
    void write(char symbol);
    void move(char direction);
    int getPosition() const;
    void setPosition(int pos);
    std::pair<int, int> getBounds() const;
    std::string toString() const;
    void clear();
    char getBlankSymbol() const { return blankSymbol; }
    size_t getUsedCells() const { return cells.size(); }
    
    std::string serialize() const;
    void deserialize(const std::string& data);
};

}

#endif
