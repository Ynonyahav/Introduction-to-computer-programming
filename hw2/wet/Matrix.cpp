
#include "Matrix.h"

//****************************************************************************//

Matrix::Matrix() :
    rows(0) , cols(0), pixels(nullptr) {}

//****************************************************************************//

Matrix::Matrix(const int n, const int m) :
    rows(n), cols(m), pixels(new int[n * m]()) {}

//****************************************************************************//

Matrix::Matrix(const Matrix& matrix) :
    rows(matrix.rows), cols(matrix.cols),
    pixels(new int[matrix.rows * matrix.cols]) {
    for (int i = 0; i < rows * cols; i++) {
        pixels[i] = matrix.pixels[i];
    }
}

//****************************************************************************//

Matrix::~Matrix() {
    delete[] pixels;
}

//****************************************************************************//

int& Matrix::operator()(const int row, const int col) {
    if (row >= rows || row < 0 || col >= cols || col < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return pixels[row * cols + col];
}

//****************************************************************************//

const int& Matrix::operator()(const int row, const int col) const {
    if (row >= rows || row < 0 || col >= cols || col < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return pixels[row * cols + col];
}

//****************************************************************************//

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        return false;
    }
    for (int i = 0; i < m1.rows * m1.cols; i++) {
        if (m1.pixels[i] != m2.pixels[i]) {
            return false;
        }
    }
    return true;
}

//****************************************************************************//

bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}

//****************************************************************************//

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << "|" << matrix(i, j);
        }
        os << "|" << std::endl;
    }
    return os;
}

//****************************************************************************//

Matrix& Matrix::operator=(const Matrix& matrix) {
    if (this != &matrix && *this != matrix) {
        if (rows != matrix.rows || cols != matrix.cols) {
            rows = matrix.rows;
            cols = matrix.cols;
            delete[] pixels;
            pixels = new int[rows * cols];
        }
        for (int i = 0; i < rows * cols; i++) {
            pixels[i] = matrix.pixels[i];
        }
    }
    return *this;
}

//****************************************************************************//

Matrix& Matrix::operator+=(const Matrix& matrix) {
    if (rows != matrix.rows && cols != matrix.cols) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < rows * cols; i++) {
        pixels[i] += matrix.pixels[i];
    }
    return *this;
}

//****************************************************************************//

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    return result += m2;
}

//****************************************************************************//

Matrix& Matrix::operator*=(const int scalar) {
    if (scalar != 1) {
        for (int i = 0; i < rows * cols; i++) {
            pixels[i] *= scalar;
        }
    }
    return *this;
}

//****************************************************************************//

Matrix operator*(const int scalar, const Matrix& matrix) {
    Matrix result(matrix);
    return result *= scalar;
}

//****************************************************************************//

Matrix operator*(const Matrix& matrix, const int scalar) {
    return scalar * matrix;
}

//****************************************************************************//

Matrix& Matrix::operator*=(const Matrix& matrix) {
    if (cols != matrix.rows) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(rows, matrix.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result(i, j) += (*this)(i, k) * matrix(k, j);
            }
        }
    }
    *this = result;
    return *this;
}

//****************************************************************************//

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1);
    return result *= m2;
}

//****************************************************************************//

Matrix Matrix::operator-() const {
    return Matrix(-1 * *this);
}

//****************************************************************************//

Matrix& Matrix::operator-=(const Matrix& matrix) {
    return *this += -matrix;
}

//****************************************************************************//

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    return m1 + -m2;
}

//****************************************************************************//

Matrix Matrix::rotateClockwise() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(j, rows - i - 1) = (*this)(i, j);
        }
    }
    return result;
}

//****************************************************************************//

Matrix Matrix::rotateCounterClockwise() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(cols - j - 1, i) = (*this)(i, j);
        }
    }
    return result;
}

//****************************************************************************//

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(j,i) = (*this)(i, j);
        }
    }
    return result;
}

