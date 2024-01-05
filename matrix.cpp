#include "headers/matrix.hpp"
#include "headers/constants.hpp"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace cst;

// constructor
Matrix::Matrix(int i, int j)
{
    set_row(i);
    set_col(j);
    data_ = new double[i * j];
    if (data_ == nullptr)
        throw std::runtime_error("memory allocation error");
}

// destructor
Matrix::~Matrix()
{
}

// copy constructor
Matrix::Matrix(const Matrix &mat)
{
    this->row_nb_ = mat.row_nb_;
    this->col_nb_ = mat.col_nb_;
    data_ = new double[mat.row_nb_ * mat.col_nb_];
    std::copy(mat.data_, mat.data_ + row_nb_ * col_nb_, data_);
}

// move constructor
Matrix::Matrix(Matrix &&mat)
{
    this->row_nb_ = mat.row_nb_;
    this->col_nb_ = mat.col_nb_;
    this->data_ = mat.data_;
    mat.data_ = nullptr; // if the pointer is null, it is not destructed
}

// getter : matrix size
int Matrix::get_row() const { return (row_nb_); }
int Matrix::get_col() const { return (col_nb_); }
// setter : matrix size
void Matrix::set_row(int i) { this->row_nb_ = i; }
void Matrix::set_col(int j) { this->col_nb_ = j; }

// overload of internal operators
int Matrix::offset(int row, int col) const
{
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

// overload of []
double Matrix::operator[](int i) const
{
    return this->data_[i];
}

// overload of []
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
    if (mat.get_row() == row_nb_)
    {
        if (mat.get_col() == col_nb_)
            assertion = (mat.data_ == data_);
    }
    return (assertion);
}

Matrix &Matrix::operator=(const Matrix &copy)
{
    set_row(copy.get_row());
    set_col(copy.get_col());
    if (&copy != this)
    {
        Matrix tmp = copy;
        double *tmp_data = data_;
        data_ = copy.data_;
        tmp.data_ = tmp_data;
    }
    return *this;
}

Matrix inverse(const int N_space, const double a, const double b, const Matrix &Id)
{
    Matrix res(N_space, N_space);
    Matrix a_temp(N_space, 1);
    Matrix d_temp(N_space, N_space);

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
    return res;
}


// overload of exterior operators
// overload of +
Matrix operator+(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.get_row();
    int p = mat1.get_col();
    int m = mat2.get_row();
    int q = mat2.get_col();
    if (n == m && p == q)
    {
        Matrix res = Matrix(n, p);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= p; j++)
            {
                res(i, j) = mat1(i, j) + mat2(i, j);
            }
        }
        return (res);
    }
    throw std::invalid_argument("Non conform matrixes");
}

// overload of -
Matrix operator-(const Matrix &mat1, const Matrix &mat2)
{
    return (mat1 + ((-1.0) * mat2));
}

// overload of *
// matrix * matrix
Matrix operator*(const Matrix &mat1, const Matrix &mat2)
{
    int n = mat1.get_row();
    int q = mat2.get_row();
    int r = mat2.get_col();
    int p = mat1.get_col();
    if (p == q)
    { // number of columns of mat1 equal to number of rows of mat2
        Matrix res = Matrix(n, r);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= r; j++)
            {
                for (int k = 1; k <= p; k++)
                {
                    res(i, j) += mat1(i, k) * mat2(k, j);
                }
            }
        }
        return (res);
    }
    throw std::invalid_argument("Non conform matrixes");
}

// matrix * scalar
Matrix operator*(const Matrix &mat, double lambda)
{
    int n = mat.get_row();
    int p = mat.get_col();
    Matrix res = Matrix(n, p);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= p; j++)
        {
            res(i, j) = mat(i, j) * lambda;
        }
    }
    return (res);
}
// scalar * matrix
Matrix operator*(double lambda, const Matrix &mat)
{
    return (mat * lambda);
}

// overload of /
// matrix / scalar
Matrix operator/(const Matrix &mat, double lambda)
{
    if (abs(lambda) < 1e-15)
        throw std::invalid_argument("Division by zero");
    int n = mat.get_row();
    int p = mat.get_col();
    Matrix res = Matrix(n, p);
    for (int i = 1; i <= mat.get_row(); i++)
    {
        for (int j = 1; j <= mat.get_col(); j++)
        {
            res(i, j) = mat(i, j) / lambda;
        }
    }
    return (res);
}

// overload of <<
std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int i = 0; i < mat.get_row(); i++)
    {
        for (int j = 0; j < mat.get_col(); j++)
        {
            if (j == 0)
                os << "|";
            os << mat(i + 1, j + 1);
            if (j != (mat.get_col() - 1))
                os << " ";
            else
                os << "|\n";
        }
    }
    return os;
}

void fill_tridiag(Matrix &A, double u, double m, double d)
{
    int s = A.get_col();
    for (int i = 2; i < s; i++)
    {
        A(i, i - 1) = d;
        A(i, i) = m;
        A(i, i + 1) = u;
    }
    A(1, 1) = m;
    A(1, 2) = u;
    A(s, s - 1) = d;
    A(s, s) = m;
}
