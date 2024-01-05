/**
 * \file matrix.h
 * This file provides the implementation of a class tamplate
 *
 * It contains the following functions :
 * - constructor
 * - copy constructor
 * - get_row retrieves the number of rows
 * - get_col retrieves the number of columns
 * - set_row sets the number of rows
 * - set_col sets the number of columns
 *
 */

#ifndef MATRIX_HPP // to avoid multiple inclusions
#define MATRIX_HPP

#include <iostream>
#include "constants.hpp"

class Matrix
{
    int row_nb_;
    int col_nb_;
    double *data_;

public:
    /**
     * \brief the  constructor for the class
     * \param i the number of rows in the matrix
     * \param j the number of columns in the matrix
     */
    Matrix(int, int);
    // destructor
    ~Matrix();
    /**
     * \brief the copy constructor for the class
     * \param mat the matrix to be copied
     */
    Matrix(const Matrix &);

    // move constructor
    Matrix(Matrix &&);

    /**
     * \brief  the getter for the number of rows in the matrix
     * \return the number of rows in the matrix
     */
    int get_row() const;

    /**
     * \brief the getter for the number of columns in the matrix
     * \return the number of columns in the matrix
     */
    int get_col() const;

    /**
     * \brief sets the number of rows in the matrix
     * \param i the desired number of rows for the matrix
     */
    void set_row(int);

    /**
     * \brief sets the number of columns in the matrix
     * \param j the desired number of columns for the matrix
     */
    void set_col(int);

    // overload of internal operators (they are inside of the class)

    /**
     * \brief transforms the two indices of a matrix into a single index for an array
     * \param i the index of the row in the matrix
     * \param j the index of the column in the matrix
     * \return the index of the array corresponding to the two matrix indices
     */
    int offset(int, int) const;

    // AMÉLIORER ICI
    /**
     * \brief overloads the operator [] for array access
     * \param i the index in the array
     * \return the value of the element at the specified index
     */
    double operator[](int) const;
    double &operator[](int);

    // AMÉLIORER ICI
    /**
     * \brief Accesses the element at the specified row and column using parentheses.
     * \param row the row index
     * \param col the column index
     * \return the value of the element at the specified row and column
     */
    double operator()(int, int) const;
    double &operator()(int, int);

    /**
     * \brief Overloads the equality operator (==) to compare two matrices for equality
     * \param other The matrix to compare with
     * \return True if the matrices are equal, false otherwise
     */
    bool operator==(const Matrix &);

    /**
     * \brief Overloads the assignment operator (=) to copy the content of another matrix
     * \param other The matrix to copy
     * \return Reference to the modified matrix after assignment
     */
    Matrix &operator=(const Matrix &);
};

/**
 * \brief Computes the inverse of a matrix using a specified method
 * \param N_space The dimension of the square matrix
 * \param a The value 'a' used in the inversion method
 * \param b The value 'b' used in the inversion method
 * \param Id The input matrix to be inverted
 * \return The inverted matrix using the specified parameters
 */
Matrix inverse(const int, const double, const double, const Matrix &);

/**
 * \brief Overloads the addition operator (+) for matrix addition.
 * \param mat1 The first matrix.
 * \param mat2 The second matrix.
 * \return The result of adding the two matrices.
 * \throws std::invalid_argument if the matrices are not conformable for addition.
 */
Matrix operator+(const Matrix &, const Matrix &); // Overload the + operator

/**
 * \brief Overloads the soustraction operator (-) for matrix subtraction
 * \param mat1 The first matrix
 * \param mat2 The second matrix
 * \return The result of subtracting the two matrices
 * \throws std::invalid_argument if the matrices are not conformable for subtraction
 */
Matrix operator-(const Matrix &, const Matrix &); // Overload the - operator

/**
 * \brief Overloads the multiplication operator (*) for matrix multiplication
 * \param mat1 The first matrix
 * \param mat2 The second matrix
 * \return The result of multiplying the two matrices
 * \throws std::invalid_argument if the matrices are not conformable for multiplication
 */
Matrix operator*(const Matrix &, const Matrix &); // matrix * matrix

/**
 * \brief Overloads the multiplication operator (*) for scalar multiplication.
 * \param mat The matrix to be multiplied.
 * \param lambda The scalar value for multiplication.
 * \return The result of multiplying the matrix by the scalar value.
 */
Matrix operator*(const Matrix &, double); // matrix * scalar

/**
 * \brief Overloads the multiplication operator (*) for scalar multiplication.
 * \param mat The matrix to be multiplied.
 * \param lambda The scalar value for multiplication.
 * \return The result of multiplying the matrix by the scalar value.
 */
Matrix operator*(double, const Matrix &); // scalar * matrix

/**
 * \brief Overloads the division operator (/) for scalar division
 * \param mat The matrix to be divided
 * \param lambda The scalar value for division
 * \return The result of dividing the matrix by the scalar value
 */
Matrix operator/(const Matrix &, double); // matrix / scalar

/**
 * \brief Overloads the output stream operator (<<) for matrix output to an ostream.
 * \param os The output stream.
 * \param mat The matrix to be output.
 * \return A reference to the output stream.
 */
std::ostream &operator<<(std::ostream &, const Matrix &); // printing

/**
 * \brief Fills a tridiagonal matrix with specified values.
 * \param A The tridiagonal matrix to be filled.
 * \param u The upper diagonal element value.
 * \param m The main diagonal element value.
 * \param d The lower diagonal element value.
 */
void fill_tridiag(Matrix &, double, double, double);

/**
 * \brief returns the maximum value within the matrix
 * \param U the matrix in which we search for the maximum value
 * \return a double representing the maximum value in the matrix
 */
double max_matrix(Matrix U);

#endif
