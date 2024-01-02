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
        throw std::runtime_error("Memory allocation error");
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
        throw std::invalid_argument("num ligne incorrect");
    if (col > get_col())
        throw std::invalid_argument("num colonne incorrect");
    if (get_col() == 1)
    {
        return (row - 1);
    }
    return (row - 1) * get_col() + (col - 1);
}

// overload of []
double Matrix::operator[](int i) const
{
    // if (i<0 || i >= row_nb_) {
    //     throw std::out_of_range("Element out of bounds!");
    // }
    return this->data_[i];
}

// overload of []
double &Matrix::operator[](int i)
{
    // if (i<0 || i >= row_nb_) {
    //     throw std::out_of_range("Element out of bounds!");
    // }
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

/*
Matrix inverse_diag(const int n, Matrix A) {
    Matrix res(n,n);
    for (int i=1; i<=n; i++) {
        res(i,i) = 1/A(i,i);
    }
    return res;
}

Matrix transpose(const int N_space, const Matrix A) {
    Matrix res(N_space, N_space);

    for (int i=1; i<=N_space; i++){
        for (int j=1; j<=N_space; j++){
            res(i,j) = A(j,i);
        }
    }
    return res;
}

Matrix inverse_gauss(const Matrix A) {
    int col = A.get_col();

    for (int i = 1; i <= col; i++){
        if (A(i,i) == 0) throw std::invalid_argument("Il y a un zéro sur la diagonale donc matrice non inversible");
    }
    Matrix temp = A;
    Matrix res = Matrix(col, col);
    for (int p = 1; p <= col; p++){
        res(p, p) = 1;
    }

    for (int k = 1; k <= col; k++){
        double var = temp(k, k);
        for (int i = 1; i <= col; i++){
            temp(k, i) = temp(k, i)/var;
            res(k, i) = res(k,i)/var;
        }

        for (int j = (k+1); j <= col; j++){
            double var1 = temp(j, k);
            for (int l = 1; l <= col; l++){
                temp(j, l) = temp(j, l) - var1 * temp(k, l);
                res(j, l) = res(j, l) - var1 * res(k, l);
            }
        }
    }
    return res;
}

Matrix inverse_block(const int N_space, const double a, const double b) {
    double coeff = - a / b; // 1+4d / d

    std::vector<Matrix> U_vect; // vector of the U matrixes addresses
    Matrix U_curr(N_space, N_space); // U_i
    Matrix U_succ(N_space, N_space); // U_i+1

    std::vector<Matrix> V_vect; // vector of the V matrixes addresses
    Matrix V_curr(N_space, N_space); // V_i
    Matrix V_prec(N_space, N_space); // V_i-1

    // U_1
    fill_tridiag(U_curr, 0, 1, 0); // Id

    // U_2
    U_succ = coeff * U_curr; // 1+4d / d * Id
    U_vect.push_back(U_curr);
    U_vect.push_back(U_succ);

    for (int i=1; i<N_space-1; i++) {
        U_vect.push_back((coeff * U_vect[i]) - U_vect[i-1]);
    }

    // V_n
    V_curr = a * U_vect[N_space] - b * transpose(N_space, U_vect[N_space-1]); // ( 1+4d U_n - d U_n-i^T ) ^ -1
    V_curr = inverse_gauss(V_curr);

    // V_n-1
    V_prec = coeff * V_curr;
    V_vect.push_back(V_curr);
    V_vect.push_back(V_prec);

    for (int i=N_space-2; i>=0; i--) {
        V_vect.push_back(coeff * V_vect[i+1] - V_vect[i+2]);
    }

    std::vector<Matrix> blocs_vect;
    for (int i=1; i<=N_space; i++) {
        for (int j=i; j<=N_space; j++) {
            blocs_vect.push_back(U_vect[i] * V_vect[j]);
        }
    }

    int n = N_space * N_space;
    Matrix res(n,n);
    // remplissage du triangle superieur de l'inverse
    for (int i=1; i<=N_space; i++) {
        for (int j=i; j<=N_space; j++) {
            int nb_bloc = (i-1)*N_space+j-i+1; // (i-1)*N_space + j-(i-1)
            Matrix fill_bloc = blocs_vect[nb_bloc];
            for (int k=1; k<=N_space; k++) {
                for (int l=1; l<=N_space; l++) {
                    // Ligne_element = (Ligne_bloc -1) * N_space + Ligne_element_dans_bloc
                    // Colonne_element = (Colonne_bloc -1) * N_space + Colonne_element_dans_bloc
                    res((i-1)*N_space+k,(j-1)*N_space+l) = fill_bloc(k,l);
                }
            }
        }
    }
    // remplissage du triangle inferieur de l'inverse par symetrie (inverse de symetrique reste symetrique)
    for (int i=1; i<=N_space; i++) {
        for (int j=1; j<=i; j++) {
            res(i,j) = res(j,i);
        }
    }

    return res;
}
*/

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
    throw std::invalid_argument("Non conform matrices");
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
    throw std::invalid_argument("Non conform matrices");
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
        throw std::invalid_argument("Cannot divide by a null scalar");
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
