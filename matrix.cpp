#include "headers/matrix.hpp"
#include "headers/constants.hpp"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace cst;

// Constructor: Initializes a matrix with the specified number of rows and columns
// Allocates memory for the matrix data and throws an exception if memory allocation fails
Matrix::Matrix(int i, int j)
{
    set_row(i);
    set_col(j);
    data_ = new double[i * j];
    if (data_ == nullptr)
        throw std::runtime_error("memory allocation error");
}

// Destructor: Cleans up allocated memory when a matrix goes out of scope
Matrix::~Matrix()
{
    // Destructor implementation, no explicit memory deallocation as it's handled by the smart pointer
}

// Copy Constructor: Creates a new matrix by copying the contents of another matrix
Matrix::Matrix(const Matrix &mat)
{
    // Copy the dimensions of the source matrix
    this->row_nb_ = mat.row_nb_;
    this->col_nb_ = mat.col_nb_;

    // Allocate memory for the new matrix
    data_ = new double[mat.row_nb_ * mat.col_nb_];

    // Copy the data from the source matrix to the new matrix
    std::copy(mat.data_, mat.data_ + row_nb_ * col_nb_, data_);
}

// Move constructor: Creates a new matrix by moving the contents of another matrix
Matrix::Matrix(Matrix &&mat)
{
    // Copy the dimensions of the source matrix
    this->row_nb_ = mat.row_nb_;
    this->col_nb_ = mat.col_nb_;

    // Move the data pointer from the source matrix to the new matrix
    this->data_ = mat.data_;

    // Set the source matrix's data pointer to null to avoid double deletion
    mat.data_ = nullptr;
}

// Getters
int Matrix::get_row() const { return (row_nb_); }
int Matrix::get_col() const { return (col_nb_); }

// Setters
void Matrix::set_row(int i) { this->row_nb_ = i; }
void Matrix::set_col(int j) { this->col_nb_ = j; }

// overload of internal operators
int Matrix::offset(int row, int col) const
{
    // Check if the row and column numbers are valid
    if (row > get_row())
        throw std::invalid_argument("invalid row number");
    if (col > get_col())
        throw std::invalid_argument("invalid column number");

    if (get_col() == 1)
    {
        return (row - 1);
    }
    return (row - 1) * get_col() + (col - 1);
}

double Matrix::operator[](int i) const
{
    return this->data_[i];
}

double &Matrix::operator[](int i)
{
    return this->data_[i];
}

double Matrix::operator()(int row, int col) const
{
    return data_[offset(row, col)];
}

double &Matrix::operator()(int row, int col)
{
    return data_[offset(row, col)];
}

// overload of =
bool Matrix::operator==(const Matrix &mat)
{
    bool assertion = 0; // false

    // Check if the dimensions are the same
    if (mat.get_row() == row_nb_)
    {
        if (mat.get_col() == col_nb_)
            // Check if the data pointers point to the same location
            assertion = (mat.data_ == data_);
    }
    return (assertion);
}

Matrix &Matrix::operator=(const Matrix &copy)
{
    // Set the dimensions of the current matrix to match the source matrix
    set_row(copy.get_row());
    set_col(copy.get_col());

    // Check for self-assignment
    if (&copy != this)
    {
        // Create a temporary matrix copy
        Matrix tmp = copy;

        // Swap data pointers to achieve assignment without unnecessary copying
        double *tmp_data = data_;
        data_ = copy.data_;
        tmp.data_ = tmp_data;
    }
    // Return the modified matrix
    return *this;
}

Matrix inverse(const int N_space, const double a, const double b, const Matrix &Id)
{
    Matrix res(N_space, N_space);
    Matrix a_temp(N_space, 1);
    Matrix d_temp(N_space, N_space);

    // Forward elimination phase of the Thomas algorithm
    a_temp(1, 1) = a / b;
    for (int j = 1; j < N_space + 1; j++)
    {
        d_temp(1, j) = Id(1, j) / b;
    }

    for (int i = 2; i < N_space + 1; i++)
    {
        for (int j = 1; j < N_space + 1; j++)
        {
            double coef = 1 / (b - a * a_temp(i - 1, 1));
            a_temp(i, 1) = a * coef;
            d_temp(i, j) = (Id(i, j) - a * d_temp(i - 1, j)) * coef;
        }
    }

    // Backward substitution phase of the Thomas algorithm
    for (int k = 1; k < N_space + 1; k++)
    {
        res(N_space, k) = d_temp(N_space, k);
    }

    for (int i = N_space - 1; i > 0; i--)
    {
        for (int j = 1; j < N_space + 1; j++)
        {
            res(i, j) = d_temp(i, j) - a_temp(i, 1) * res(i + 1, j);
        }
    }
    // Return the inverse matrix
    return res;
}

Matrix operator+(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.get_row();
    int p = mat1.get_col();
    int m = mat2.get_row();
    int q = mat2.get_col();

    // Check if the dimensions are the same
    if (n == m && p == q)
    {
        // Create a new matrix to store the result
        Matrix res = Matrix(n, p);

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= p; j++)
            {
                // Add the corresponding elements of the two matrices
                res(i, j) = mat1(i, j) + mat2(i, j);
            }
        }
        return (res);
    }
    // Throw an exception if the dimensions are not the same
    throw std::invalid_argument("Non conform matrixes");
}

Matrix operator-(const Matrix &mat1, const Matrix &mat2)
{
    return (mat1 + ((-1.0) * mat2));
}

Matrix operator*(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.get_row();
    int q = mat2.get_row();
    int r = mat2.get_col();
    int p = mat1.get_col();

    // Check if the dimensions are the same
    if (p == q)
    {
        // Create a new matrix to store the result
        Matrix res = Matrix(n, r);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= r; j++)
            {
                for (int k = 1; k <= p; k++)
                {
                    // Multiply the corresponding elements of the two matrices
                    res(i, j) += mat1(i, k) * mat2(k, j);
                }
            }
        }
        return (res);
    }
    // Throw an exception if the dimensions are not the same
    throw std::invalid_argument("Non conform matrixes");
}

Matrix operator*(const Matrix &mat, double lambda)
{
    int n = mat.get_row();
    int p = mat.get_col();

    // Create a new matrix to store the result
    Matrix res = Matrix(n, p);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= p; j++)
        {
            // Multiply each element of the matrix by the scalar
            res(i, j) = mat(i, j) * lambda;
        }
    }
    return (res);
}

Matrix operator*(double lambda, const Matrix &mat)
{
    return (mat * lambda);
}

Matrix operator/(const Matrix &mat, double lambda)
{
    // Throw an exception if the scalar is zero
    if (abs(lambda) < 1e-15)
        throw std::invalid_argument("Division by zero");

    int n = mat.get_row();
    int p = mat.get_col();

    // Create a new matrix to store the result
    Matrix res = Matrix(n, p);

    for (int i = 1; i <= mat.get_row(); i++)
    {
        for (int j = 1; j <= mat.get_col(); j++)
        {
            // Divide each element of the matrix by the scalar
            res(i, j) = mat(i, j) / lambda;
        }
    }
    return (res);
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int i = 0; i < mat.get_row(); i++)
    {
        for (int j = 0; j < mat.get_col(); j++)
        {
            if (j == 0)
                os << "|";
            // Print the element
            os << mat(i + 1, j + 1);
            if (j != (mat.get_col() - 1))
                os << " ";
            else
                os << "|\n";
        }
    }
    // Return the output stream
    return os;
}

void fill_tridiag(Matrix &A, double u, double m, double d)
{
    int s = A.get_col();
    for (int i = 2; i < s; i++)
    {
        // Fill the upper diagonal
        A(i, i - 1) = d;
        // Fill the main diagonal
        A(i, i) = m;
        // Fill the lower diagonal
        A(i, i + 1) = u;
    }
    // Fill the first and last elements of the matrix
    A(1, 1) = m;
    A(1, 2) = u;
    A(s, s - 1) = d;
    A(s, s) = m;
}

double max_matrix(Matrix U)
{
    double max = 0;

    // Iterate over the space dimension (rows)
    for (int i = 1; i < N_space + 1; i++)
    {
        // Iterate over a limited number of time steps (columns) for performance
        for (int j = 1; j < 101; j++)
        {
            if (U(i, j * 10) > max)
                max = U(i, j * 10);
        }
    }
    return max;
}