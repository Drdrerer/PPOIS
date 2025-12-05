#include "Tape.h"

namespace turing_machine {

Tape::Tape(const std::string& initialData, char blank) 
    : headPosition(0), blankSymbol(blank) {
    for (size_t i = 0; i < initialData.length(); ++i) {
        cells[static_cast<int>(i)] = initialData[i];
    }
}

Tape::Tape(const Tape& other) 
    : cells(other.cells), headPosition(other.headPosition), blankSymbol(other.blankSymbol) {
}

Tape& Tape::operator=(const Tape& other) {
    if (this != &other) {
        cells = other.cells;
        headPosition = other.headPosition;
        blankSymbol = other.blankSymbol;
    }
    return *this;
}

char Tape::read() const {
    auto it = cells.find(headPosition);
    if (it != cells.end()) {
        return it->second;
    }
    return blankSymbol;
}

void Tape::write(char symbol) {
    if (symbol != blankSymbol) {
        cells[headPosition] = symbol;
    } else {
        cells.erase(headPosition);
    }
}

void Tape::move(char direction) {
    if (direction == 'R') {
        headPosition++;
    } else if (direction == 'L') {
        headPosition--;
    }
}

int Tape::getPosition() const {
    return headPosition;
}

void Tape::setPosition(int pos) {
    headPosition = pos;
}

std::pair<int, int> Tape::getBounds() const {
    if (cells.empty()) {
        return {headPosition, headPosition};
    }
    
    int minPos = headPosition;
    int maxPos = headPosition;
    
    for (const auto& cell : cells) {
        if (cell.first < minPos) minPos = cell.first;
        if (cell.first > maxPos) maxPos = cell.first;
    }
    
    return {minPos, maxPos};
}

std::string Tape::toString() const {
    auto bounds = getBounds();
    std::string result;
    
    for (int i = bounds.first; i <= bounds.second; ++i) {
        if (i == headPosition) {
            result += "[";
            result += read();
            result += "]";
        } else {
            auto it = cells.find(i);
            if (it != cells.end()) {
                result += it->second;
            } else {
                result += blankSymbol;
            }
        }
        if (i < bounds.second) {
            result += " ";
        }
    }
    
    return result;
}

void Tape::clear() {
    cells.clear();
    headPosition = 0;
}

std::string Tape::serialize() const {
    std::ostringstream oss;
    oss << headPosition << " " << blankSymbol << " " << cells.size() << " ";
    for (const auto& cell : cells) {
        oss << cell.first << " " << cell.second << " ";
    }
    return oss.str();
}

void Tape::deserialize(const std::string& data) {
    std::istringstream iss(data);
    int cellCount;
    iss >> headPosition >> blankSymbol >> cellCount;
    cells.clear();
    for (int i = 0; i < cellCount; ++i) {
        int pos;
        char symbol;
        iss >> pos >> symbol;
        cells[pos] = symbol;
    }
}

}
