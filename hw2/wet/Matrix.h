#pragma once

#include "Utilities.h"
#include <ostream>

/**
 * @class Matrix
 * @brief Represents a 2D matrix of integers.
 */
class Matrix {

    int rows; /**< Number of rows in the matrix */
    int cols; /**< Number of columns in the matrix */
    int* pixels; /**< Pointer to the array of matrix elements */

public:

    /**default constructor with cols and rows set to 0 and pixels set to nullptr*/
    Matrix();

    /**
     * @brief Constructs a Matrix with the given dimensions.
     * @param rows The number of rows.
     * @param cols The number of columns.
     */
    Matrix(int rows, int cols);

    /**
     * @brief Copy constructor for Matrix.
     * @param other The Matrix object to copy from.
     */
    Matrix(const Matrix& other);

    /**
     * @brief Destructor for Matrix.
     */
    ~Matrix();

    /**
     * @brief Accesses an element in the matrix.
     * @param row The row index.
     * @param col The column index.
     * @return A reference to the element at the specified position.
     * @throws if the indices are out of bounds.
     */
    int& operator()(int row, int col);

    /**
     * @brief Accesses an element in the matrix (const version).
     * @param row The row index.
     * @param col The column index.
     * @return A const reference to the element at the specified position.
     * @throws if the indices are out of bounds.
     */
    const int& operator()(int row, int col) const;

    /**
     * @brief Compares two matrices for equality.
     * @param leftMatrix The first matrix.
     * @param rightMatrix The second matrix.
     * @return True if the matrices are equal, false otherwise.
     */
    friend bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix);

    /**
     * @brief Outputs the matrix to a stream.
     * @param os The output stream.
     * @param matrix The matrix to output.
     * @return The output stream with the matrix's data.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    /**
     * @brief Assignment operator for Matrix.
     * @param other The Matrix object to assign from.
     * @return A reference to the assigned Matrix object.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Adds another matrix to this matrix.
     * @param other The matrix to add.
     * @return A reference to the updated Matrix object.
     * @throws if the matrices have different dimensions.
     */
    Matrix& operator+=(const Matrix& other);

    /**
     * @brief Multiplies this matrix by a scalar.
     * @param scalar The scalar to multiply by.
     * @return A reference to the updated Matrix object.
     */
    Matrix& operator*=(int scalar);

    /**
     * @brief Multiplies this matrix by another matrix.
     * @param other The matrix to multiply by.
     * @return A reference to the updated Matrix object.
     * @throws if the matrices have cannot be multiplied (incompatible dimensions).
     */
    Matrix& operator*=(const Matrix& other);

    /**
     * @brief Negates the matrix (element-wise).
     * @return A new negated Matrix object.
     */
    Matrix operator-() const;

    /**
     * @brief Subtracts another matrix from this matrix.
     * @param other The matrix to subtract.
     * @return A reference to the updated Matrix object.
     * @throws if the matrices have different dimensions.
     */
    Matrix& operator-=(const Matrix& other);

    /**
     * @brief Rotates the matrix 90 degrees clockwise.
     * @return A new rotated Matrix object.
     */
    Matrix rotateClockwise();

    /**
     * @brief Rotates the matrix 90 degrees counter-clockwise.
     * @return A new rotated Matrix object.
     */
    Matrix rotateCounterClockwise();

    /**
     * @brief Transposes the matrix (rows become columns and vice versa).
     * @return A new transposed Matrix object.
     */
    Matrix transpose();
};

/**
 * @brief Compares two matrices for inequality.
 * @param leftMatrix The first matrix.
 * @param rightMatrix The second matrix.
 * @return True if the matrices are not equal, false otherwise.
 */
bool operator!=(const Matrix& leftMatrix, const Matrix& rightMatrix);

/**
 * @brief Adds two matrices.
 * @param leftMatrix The first matrix.
 * @param rightMatrix The second matrix.
 * @return A new Matrix object that is the sum of leftMatrix and rightMatrix.
 * @throws if the matrices have different dimensions.
 */
Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix);

/**
 * @brief Multiplies a matrix by a scalar.
 * @param scalar The scalar to multiply by.
 * @param matrix The matrix to multiply.
 * @return A new Matrix object that is the result of the multiplication.
 */
Matrix operator*(int scalar, const Matrix& matrix);

/**
 * @brief Multiplies a matrix by a scalar.
 * @param matrix The matrix to multiply.
 * @param scalar The scalar to multiply by.
 * @return A new Matrix object that is the result of the multiplication.
 */
Matrix operator*(const Matrix& matrix, int scalar);

/**
 * @brief Multiplies two matrices.
 * @param leftMatrix The first matrix.
 * @param rightMatrix The second matrix.
 * @return A new Matrix object that is the result of the multiplication.
 * @throws if the matrices have cannot be multiplied (incompatible dimensions).
 */
Matrix operator*(const Matrix& leftMatrix, const Matrix& rightMatrix);

/**
 * @brief Subtracts one matrix from another.
 * @param leftMatrix The first matrix.
 * @param rightMatrix The second matrix.
 * @return A new Matrix object that is the result of the subtraction.
 * @throws if the matrices have different dimensions.
 */
Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix);
