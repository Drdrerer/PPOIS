#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <algorithm>

void Matrix::setupMemory(int r, int c) {
    elements = new double* [r];
    for (int i = 0; i < r; ++i) {
        elements[i] = new double[c]();
    }
}

void Matrix::cleanupMemory() {
    if (elements) {
        for (int i = 0; i < numRows; ++i) {
            delete[] elements[i];
        }
        delete[] elements;
        elements = nullptr;
    }
}

void Matrix::duplicateContent(const Matrix& source) {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            elements[i][j] = source.elements[i][j];
        }
    }
}

Matrix::Matrix(int r, int c) : numRows(r), numCols(c) {
    if (r <= 0 || c <= 0) {
        throw std::invalid_argument("Количество строк и столбцов должно быть больше нуля");
    }
    setupMemory(numRows, numCols);
}

Matrix::Matrix(const Matrix& source) : numRows(source.numRows), numCols(source.numCols) {
    setupMemory(numRows, numCols);
    duplicateContent(source);
}

Matrix::~Matrix() {
    cleanupMemory();
}

Matrix& Matrix::operator=(const Matrix& source) {
    if (this != &source) {
        cleanupMemory();
        numRows = source.numRows;
        numCols = source.numCols;
        setupMemory(numRows, numCols);
        duplicateContent(source);
    }
    return *this;
}

int Matrix::rowCount() const { return numRows; }
int Matrix::columnCount() const { return numCols; }

double* Matrix::operator[](int idx) {
    if (idx < 0 || idx >= numRows) {
        throw std::out_of_range("Некорректный индекс строки");
    }
    return elements[idx];
}

const double* Matrix::operator[](int idx) const {
    if (idx < 0 || idx >= numRows) {
        throw std::out_of_range("Некорректный индекс строки");
    }
    return elements[idx];
}

Matrix& Matrix::operator++() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            ++elements[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}

Matrix& Matrix::operator--() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            --elements[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    --(*this);
    return temp;
}

void Matrix::changeSize(int newRows, int newCols) {
    if (newRows <= 0 || newCols <= 0) {
        throw std::invalid_argument("Новые размеры должны быть положительными числами");
    }

    if (newRows == numRows && newCols == numCols) {
        return;
    }

    double** newElements = new double* [newRows];
    for (int i = 0; i < newRows; ++i) {
        newElements[i] = new double[newCols]();
    }

    int rowsToCopy = std::min(numRows, newRows);
    int colsToCopy = std::min(numCols, newCols);
    for (int i = 0; i < rowsToCopy; ++i) {
        for (int j = 0; j < colsToCopy; ++j) {
            newElements[i][j] = elements[i][j];
        }
    }

    cleanupMemory();
    elements = newElements;
    numRows = newRows;
    numCols = newCols;
}

void Matrix::readFromFile(const std::string& filepath) {
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Ошибка открытия файла: " + filepath);
    }

    int r, c;
    inputFile >> r >> c;

    if (r <= 0 || c <= 0) {
        throw std::runtime_error("Неверные размеры матрицы в файле");
    }

    changeSize(r, c);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (!(inputFile >> elements[i][j])) {
                throw std::runtime_error("Ошибка при чтении данных из файла");
            }
        }
    }

    inputFile.close();
}

void Matrix::writeToFile(const std::string& filepath) const {
    std::ofstream outputFile(filepath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Ошибка создания файла: " + filepath);
    }

    outputFile << numRows << " " << numCols << std::endl;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            outputFile << std::setw(10) << elements[i][j] << " ";
        }
        outputFile << std::endl;
    }

    outputFile.close();
}

Matrix Matrix::extractPart(int beginRow, int beginCol, int partRows, int partCols) const {
    if (beginRow < 0 || beginCol < 0 ||
        beginRow + partRows > numRows || beginCol + partCols > numCols) {
        throw std::out_of_range("Неверные параметры для извлечения части матрицы");
    }

    Matrix part(partRows, partCols);
    for (int i = 0; i < partRows; ++i) {
        for (int j = 0; j < partCols; ++j) {
            part[i][j] = elements[beginRow + i][beginCol + j];
        }
    }
    return part;
}

Matrix Matrix::getTransposed() const {
    Matrix result(numCols, numRows);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            result[j][i] = elements[i][j];
        }
    }
    return result;
}

bool Matrix::hasEqualDimensions() const {
    return numRows == numCols;
}

bool Matrix::isDiagonalMatrix() const {
    if (!hasEqualDimensions()) return false;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (i != j && std::abs(elements[i][j]) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isAllZeros() const {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (std::abs(elements[i][j]) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isUnitMatrix() const {
    if (!hasEqualDimensions()) return false;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (i == j) {
                if (std::abs(elements[i][j] - 1.0) > 1e-10) {
                    return false;
                }
            }
            else {
                if (std::abs(elements[i][j]) > 1e-10) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Matrix::isSymmetricMatrix() const {
    if (!hasEqualDimensions()) return false;

    for (int i = 0; i < numRows; ++i) {
        for (int j = i + 1; j < numCols; ++j) {
            if (std::abs(elements[i][j] - elements[j][i]) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isUpperTriangle() const {
    if (!hasEqualDimensions()) return false;

    for (int i = 1; i < numRows; ++i) {
        for (int j = 0; j < i; ++j) {
            if (std::abs(elements[i][j]) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isLowerTriangle() const {
    if (!hasEqualDimensions()) return false;

    for (int i = 0; i < numRows; ++i) {
        for (int j = i + 1; j < numCols; ++j) {
            if (std::abs(elements[i][j]) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

void Matrix::display() const {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << std::setw(8) << elements[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::setAllValues(double val) {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            elements[i][j] = val;
        }
    }
}

bool Matrix::isSimilar(const Matrix& other, double eps) const {
    if (numRows != other.numRows || numCols != other.numCols) {
        return false;
    }

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (std::abs(elements[i][j] - other.elements[i][j]) > eps) {
                return false;
            }
        }
    }
    return true;
}