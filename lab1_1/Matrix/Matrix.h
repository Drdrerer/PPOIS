#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
private:
    double** elements;
    int numRows;
    int numCols;

    void setupMemory(int r, int c);
    void cleanupMemory();
    void duplicateContent(const Matrix& source);

public:
    Matrix(int r = 1, int c = 1);
    Matrix(const Matrix& source);
    ~Matrix();

    Matrix& operator=(const Matrix& source);

    int rowCount() const;
    int columnCount() const;

    double* operator[](int idx);
    const double* operator[](int idx) const;

    Matrix& operator++();
    Matrix operator++(int);
    Matrix& operator--();
    Matrix operator--(int);

    void changeSize(int newRows, int newCols);
    void readFromFile(const std::string& filepath);
    void writeToFile(const std::string& filepath) const;
    Matrix extractPart(int beginRow, int beginCol, int partRows, int partCols) const;
    Matrix getTransposed() const;

    bool hasEqualDimensions() const;
    bool isDiagonalMatrix() const;
    bool isAllZeros() const;
    bool isUnitMatrix() const;
    bool isSymmetricMatrix() const;
    bool isUpperTriangle() const;
    bool isLowerTriangle() const;

    void display() const;
    void setAllValues(double val);
    bool isSimilar(const Matrix& other, double eps = 1e-10) const;
};

#endif