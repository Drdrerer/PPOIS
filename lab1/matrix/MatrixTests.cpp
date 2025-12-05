#include "Matrix.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cmath>

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream file1("test_data1.txt");
        file1 << "2 3\n1.0 2.0 3.0\n4.0 5.0 6.0";
        file1.close();

        std::ofstream file2("test_data2.txt");
        file2 << "3 3\n1.0 0.0 0.0\n0.0 1.0 0.0\n0.0 0.0 1.0";
        file2.close();

        std::ofstream file3("test_data3.txt");
        file3 << "2 2\n1.0 2.0\n2.0 1.0";
        file3.close();
    }

    void TearDown() override {
        remove("test_data1.txt");
        remove("test_data2.txt");
        remove("test_data3.txt");
        remove("output_data.txt");
    }
};

TEST_F(MatrixTest, BasicConstructor) {
    Matrix m;
    EXPECT_EQ(m.rowCount(), 1);
    EXPECT_EQ(m.columnCount(), 1);
    EXPECT_DOUBLE_EQ(m[0][0], 0.0);
}

TEST_F(MatrixTest, SizedConstructor) {
    Matrix m(3, 4);
    EXPECT_EQ(m.rowCount(), 3);
    EXPECT_EQ(m.columnCount(), 4);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(m[i][j], 0.0);
        }
    }
}

TEST_F(MatrixTest, InvalidConstructorParams) {
    EXPECT_THROW(Matrix m(0, 5), std::invalid_argument);
    EXPECT_THROW(Matrix m(5, 0), std::invalid_argument);
    EXPECT_THROW(Matrix m(-1, 5), std::invalid_argument);
}

TEST_F(MatrixTest, CopyConstructor) {
    Matrix original(2, 2);
    original[0][0] = 1.0; original[0][1] = 2.0;
    original[1][0] = 3.0; original[1][1] = 4.0;

    Matrix copy(original);
    EXPECT_EQ(copy.rowCount(), 2);
    EXPECT_EQ(copy.columnCount(), 2);
    EXPECT_DOUBLE_EQ(copy[0][0], 1.0);
    EXPECT_DOUBLE_EQ(copy[0][1], 2.0);
    EXPECT_DOUBLE_EQ(copy[1][0], 3.0);
    EXPECT_DOUBLE_EQ(copy[1][1], 4.0);
}

TEST_F(MatrixTest, AssignmentOperator) {
    Matrix original(2, 2);
    original[0][0] = 1.0; original[0][1] = 2.0;
    original[1][0] = 3.0; original[1][1] = 4.0;

    Matrix assigned;
    assigned = original;
    EXPECT_TRUE(assigned.isSimilar(original));
}

TEST_F(MatrixTest, SelfAssignment) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    m = m; 
    EXPECT_DOUBLE_EQ(m[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[0][1], 2.0);
    EXPECT_DOUBLE_EQ(m[1][0], 3.0);
    EXPECT_DOUBLE_EQ(m[1][1], 4.0);
}

TEST_F(MatrixTest, ElementAccess) {
    Matrix m(2, 2);
    m[0][0] = 1.5;
    m[1][1] = 2.5;

    EXPECT_DOUBLE_EQ(m[0][0], 1.5);
    EXPECT_DOUBLE_EQ(m[1][1], 2.5);
}

TEST_F(MatrixTest, ConstElementAccess) {
    const Matrix m(2, 2);
    EXPECT_DOUBLE_EQ(m[0][0], 0.0);
}

TEST_F(MatrixTest, InvalidElementAccess) {
    Matrix m(2, 2);
    EXPECT_THROW(m[5][0] = 0.0, std::out_of_range);
    EXPECT_THROW(m[-1][0] = 0.0, std::out_of_range);
}

TEST_F(MatrixTest, PreIncrement) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    ++m;
    EXPECT_DOUBLE_EQ(m[0][0], 2.0);
    EXPECT_DOUBLE_EQ(m[0][1], 3.0);
    EXPECT_DOUBLE_EQ(m[1][0], 4.0);
    EXPECT_DOUBLE_EQ(m[1][1], 5.0);
}

TEST_F(MatrixTest, PostIncrement) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    Matrix old = m++;
    EXPECT_DOUBLE_EQ(old[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[0][0], 2.0);
}

TEST_F(MatrixTest, PreDecrement) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    --m;
    EXPECT_DOUBLE_EQ(m[0][0], 0.0);
    EXPECT_DOUBLE_EQ(m[0][1], 1.0);
    EXPECT_DOUBLE_EQ(m[1][0], 2.0);
    EXPECT_DOUBLE_EQ(m[1][1], 3.0);
}

TEST_F(MatrixTest, PostDecrement) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    Matrix old = m--;
    EXPECT_DOUBLE_EQ(old[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[0][0], 0.0);
}

TEST_F(MatrixTest, Resize) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    m.changeSize(3, 3);
    EXPECT_EQ(m.rowCount(), 3);
    EXPECT_EQ(m.columnCount(), 3);
    EXPECT_DOUBLE_EQ(m[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[0][1], 2.0);
    EXPECT_DOUBLE_EQ(m[1][0], 3.0);
    EXPECT_DOUBLE_EQ(m[1][1], 4.0);
    EXPECT_DOUBLE_EQ(m[2][2], 0.0);
}

TEST_F(MatrixTest, InvalidResize) {
    Matrix m(2, 2);
    EXPECT_THROW(m.changeSize(0, 5), std::invalid_argument);
    EXPECT_THROW(m.changeSize(5, -1), std::invalid_argument);
}

TEST_F(MatrixTest, FileRead) {
    Matrix m;
    m.readFromFile("test_data1.txt");

    EXPECT_EQ(m.rowCount(), 2);
    EXPECT_EQ(m.columnCount(), 3);
    EXPECT_DOUBLE_EQ(m[0][0], 1.0);
    EXPECT_DOUBLE_EQ(m[0][1], 2.0);
    EXPECT_DOUBLE_EQ(m[0][2], 3.0);
    EXPECT_DOUBLE_EQ(m[1][0], 4.0);
    EXPECT_DOUBLE_EQ(m[1][1], 5.0);
    EXPECT_DOUBLE_EQ(m[1][2], 6.0);
}

TEST_F(MatrixTest, FileWrite) {
    Matrix m(2, 2);
    m[0][0] = 1.5; m[0][1] = 2.5;
    m[1][0] = 3.5; m[1][1] = 4.5;

    m.writeToFile("output_data.txt");

    Matrix loaded;
    loaded.readFromFile("output_data.txt");
    EXPECT_TRUE(loaded.isSimilar(m));
}

TEST_F(MatrixTest, ReadMissingFile) {
    Matrix m;
    EXPECT_THROW(m.readFromFile("missing.txt"), std::runtime_error);
}

TEST_F(MatrixTest, ExtractSubmatrix) {
    Matrix m(3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m[i][j] = i * 3 + j + 1;
        }
    }

    Matrix part = m.extractPart(1, 1, 2, 2);
    EXPECT_EQ(part.rowCount(), 2);
    EXPECT_EQ(part.columnCount(), 2);
    EXPECT_DOUBLE_EQ(part[0][0], 5.0);
    EXPECT_DOUBLE_EQ(part[0][1], 6.0);
    EXPECT_DOUBLE_EQ(part[1][0], 8.0);
    EXPECT_DOUBLE_EQ(part[1][1], 9.0);
}

TEST_F(MatrixTest, InvalidSubmatrix) {
    Matrix m(2, 2);
    EXPECT_THROW(m.extractPart(1, 1, 2, 2), std::out_of_range);
    EXPECT_THROW(m.extractPart(-1, 0, 1, 1), std::out_of_range);
}

TEST_F(MatrixTest, SquareCheck) {
    Matrix square(3, 3);
    Matrix nonSquare(2, 3);

    EXPECT_TRUE(square.hasEqualDimensions());
    EXPECT_FALSE(nonSquare.hasEqualDimensions());
}

TEST_F(MatrixTest, DiagonalCheck) {
    Matrix diagonal(3, 3);
    diagonal[0][0] = 1.0;
    diagonal[1][1] = 2.0;
    diagonal[2][2] = 3.0;

    Matrix nonDiagonal(3, 3);
    nonDiagonal[0][1] = 0.1;

    EXPECT_TRUE(diagonal.isDiagonalMatrix());
    EXPECT_FALSE(nonDiagonal.isDiagonalMatrix());
    EXPECT_FALSE(Matrix(2, 3).isDiagonalMatrix());
}

TEST_F(MatrixTest, ZeroCheck) {
    Matrix zero(2, 2);
    Matrix nonZero(2, 2);
    nonZero[0][0] = 0.1;

    EXPECT_TRUE(zero.isAllZeros());
    EXPECT_FALSE(nonZero.isAllZeros());
}

TEST_F(MatrixTest, IdentityCheck) {
    Matrix identity(3, 3);
    identity[0][0] = 1.0;
    identity[1][1] = 1.0;
    identity[2][2] = 1.0;

    Matrix nonIdentity(3, 3);
    nonIdentity[0][0] = 1.0;
    nonIdentity[0][1] = 0.1;

    EXPECT_TRUE(identity.isUnitMatrix());
    EXPECT_FALSE(nonIdentity.isUnitMatrix());
    EXPECT_FALSE(Matrix(2, 3).isUnitMatrix());
}

TEST_F(MatrixTest, SymmetricCheck) {
    Matrix symmetric(3, 3);
    symmetric[0][0] = 1.0; symmetric[0][1] = 2.0; symmetric[0][2] = 3.0;
    symmetric[1][0] = 2.0; symmetric[1][1] = 4.0; symmetric[1][2] = 5.0;
    symmetric[2][0] = 3.0; symmetric[2][1] = 5.0; symmetric[2][2] = 6.0;

    Matrix nonSymmetric(3, 3);
    nonSymmetric[0][1] = 1.0;
    nonSymmetric[1][0] = 2.0;

    EXPECT_TRUE(symmetric.isSymmetricMatrix());
    EXPECT_FALSE(nonSymmetric.isSymmetricMatrix());
    EXPECT_FALSE(Matrix(2, 3).isSymmetricMatrix());
}

TEST_F(MatrixTest, UpperTriangleCheck) {
    Matrix upper(3, 3);
    upper[0][0] = 1.0; upper[0][1] = 2.0; upper[0][2] = 3.0;
    upper[1][1] = 4.0; upper[1][2] = 5.0;
    upper[2][2] = 6.0;

    Matrix nonUpper(3, 3);
    nonUpper[1][0] = 0.1;

    EXPECT_TRUE(upper.isUpperTriangle());
    EXPECT_FALSE(nonUpper.isUpperTriangle());
    EXPECT_FALSE(Matrix(2, 3).isUpperTriangle());
}

TEST_F(MatrixTest, LowerTriangleCheck) {
    Matrix lower(3, 3);
    lower[0][0] = 1.0;
    lower[1][0] = 2.0; lower[1][1] = 3.0;
    lower[2][0] = 4.0; lower[2][1] = 5.0; lower[2][2] = 6.0;

    Matrix nonLower(3, 3);
    nonLower[0][1] = 0.1;

    EXPECT_TRUE(lower.isLowerTriangle());
    EXPECT_FALSE(nonLower.isLowerTriangle());
    EXPECT_FALSE(Matrix(2, 3).isLowerTriangle());
}

TEST_F(MatrixTest, Transpose) {
    Matrix m(2, 3);
    m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
    m[1][0] = 4.0; m[1][1] = 5.0; m[1][2] = 6.0;

    Matrix transposed = m.getTransposed();
    EXPECT_EQ(transposed.rowCount(), 3);
    EXPECT_EQ(transposed.columnCount(), 2);
    EXPECT_DOUBLE_EQ(transposed[0][0], 1.0);
    EXPECT_DOUBLE_EQ(transposed[0][1], 4.0);
    EXPECT_DOUBLE_EQ(transposed[1][0], 2.0);
    EXPECT_DOUBLE_EQ(transposed[1][1], 5.0);
    EXPECT_DOUBLE_EQ(transposed[2][0], 3.0);
    EXPECT_DOUBLE_EQ(transposed[2][1], 6.0);
}

TEST_F(MatrixTest, DoubleTranspose) {
    Matrix m(2, 3);
    m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
    m[1][0] = 4.0; m[1][1] = 5.0; m[1][2] = 6.0;

    Matrix doubleTransposed = m.getTransposed().getTransposed();
    EXPECT_TRUE(doubleTransposed.isSimilar(m));
}

TEST_F(MatrixTest, Fill) {
    Matrix m(2, 2);
    m.setAllValues(5.5);

    EXPECT_DOUBLE_EQ(m[0][0], 5.5);
    EXPECT_DOUBLE_EQ(m[0][1], 5.5);
    EXPECT_DOUBLE_EQ(m[1][0], 5.5);
    EXPECT_DOUBLE_EQ(m[1][1], 5.5);
}

TEST_F(MatrixTest, SimilarityCheck) {
    Matrix m1(2, 2);
    m1[0][0] = 1.0; m1[0][1] = 2.0;
    m1[1][0] = 3.0; m1[1][1] = 4.0;

    Matrix m2(2, 2);
    m2[0][0] = 1.0; m2[0][1] = 2.0;
    m2[1][0] = 3.0; m2[1][1] = 4.0;

    Matrix m3(2, 2);
    m3[0][0] = 1.1; m3[0][1] = 2.0;
    m3[1][0] = 3.0; m3[1][1] = 4.0;

    EXPECT_TRUE(m1.isSimilar(m2));
    EXPECT_FALSE(m1.isSimilar(m3));
    EXPECT_FALSE(m1.isSimilar(Matrix(3, 3)));
}

TEST_F(MatrixTest, ComplexOperations) {
    Matrix m(3, 3);
    m.setAllValues(2.0);

    Matrix result = (++m).getTransposed();
    EXPECT_EQ(result.rowCount(), 3);
    EXPECT_EQ(result.columnCount(), 3);
    EXPECT_DOUBLE_EQ(result[0][0], 3.0);
}

TEST_F(MatrixTest, OperationChain) {
    Matrix m(2, 2);
    m[0][0] = 1.0; m[0][1] = 2.0;
    m[1][0] = 3.0; m[1][1] = 4.0;

    Matrix result = m.getTransposed().extractPart(0, 0, 2, 2);
    EXPECT_TRUE(result.isSimilar(m.getTransposed()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
