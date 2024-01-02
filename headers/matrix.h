/**
 * \file matrix.h
 * This file implements the definition of a class tamplate
 *
 * It contains x functions :
 * - the constructor
 * - the copy constructor
 * - get_row allows to have the number of rows
 * - get_col allows to have the number of columns
 * - set_row allows to set the number of rows
 * - set_col allows to set the number of columns
 *
 */

#ifndef MATRIX_H // to avoid multiple inclusions
#define MATRIX_H

#include <iostream>

class Matrix
{
    int row_nb_;
    int col_nb_;
    double *data_;

public:
    /**
     * \brief the  constructor of the class
     * \param i the number of rows of the matrix
     * \param j the number of columns of the matrix
     */
    Matrix(int, int);
    // destructor
    ~Matrix();
    /**
     * \brief the copy constructor of the class
     * \param mat the matrix we want to copy
     */
    Matrix(const Matrix &);

    // move constructor
    Matrix(Matrix &&);

    // getter : matrix size
    /**
     * \brief the getter of the number of rows of the matrix
     * \return the number of rows in the matrix
     */
    int get_row() const;

    /**
     * \brief the getter of the number of columns of the matrix
     * \return the number of columns in the matrix
     */
    int get_col() const;

    /**
     * \brief sets the number of rows in the matrix
     * \param i the number of rows we want to set for the matrix
     */
    void set_row(int);

    /**
     * \brief sets the number of columns in the matrix
     * \param j the number of columns we want to set for the matrix
     */
    void set_col(int);

    // overload of internal operators (they are inside of the class)

    /**
     * \brief transforms the two indices of a matrix into a single index for an array
     * \param i the index of the line in the matrix
     * \param j the index of the column in the matrix
     * \return the index of the array corresponding to the two indices of the matrix
     */
    int offset(int, int) const;

    /**
     * \brief overloads the operator []
     * \param i the index in the array
     * \return
     */
    double operator[](int) const;
    double &operator[](int);
    /**
     * \brief overloads the operator ()
     */
    double operator()(int, int) const;
    double &operator()(int, int);

    /**
     * \brief overloads the operator =
     */
    bool operator==(const Matrix &);

    Matrix &operator=(const Matrix &);
};

/**
 * \brief returns the inverse of the matrix put in parameter
 * \param mat the matrix we want to inverse
 * \return the inverse of the matrix
 */
Matrix inverse(const int, const double, const double, const Matrix &);

/*
Matrix inverse_diag(const int, Matrix);

Matrix inverse_gauss(const Matrix);

Matrix inverse_block(const int, const double, const double);

Matrix transpose(const int, const Matrix);
*/

// overload of exterior operators (they are outside of the class)
/**
 * \brief overloads the operator +
 */
Matrix operator+(const Matrix &, const Matrix &); // Overload the + operator

/**
 * \brief overloads the operator -
 */
Matrix operator-(const Matrix &, const Matrix &); // Overload the - operator

/**
 * \brief overloads the operator * between two Matrix
 */
Matrix operator*(const Matrix &, const Matrix &); // matrix * matrix

/**
 * \brief overloads the operator * between a matrix and a double
 */
Matrix operator*(const Matrix &, double); // matrix * scalar

/**
 * \brief overloads the operator * between a double and a matrix
 */
Matrix operator*(double, const Matrix &); // scalar * matrix

/**
 * \brief overloads the operator / between a matrix and a double
 */
Matrix operator/(const Matrix &, double); // matrix / scalar

/**
 * \brief overloads the operator << to use it with a matrix
 */
std::ostream &operator<<(std::ostream &, const Matrix &); // printing

/**
 * \brief fills a tridiagonal matrix
 */
void fill_tridiag(Matrix &, double, double, double);

#endif
