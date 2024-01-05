#include "headers/matrix.hpp"
#include "headers/constants.hpp"
#include "headers/surface.hpp"

#include <cmath>
#include <vector>

using namespace std;
using namespace cst;

Matrix F_surface()
{
    Matrix F(N_space, N_space);
    double elt = tmax * pow(f, 2);
    // [L/6; 2*L/6] x [L/6; 2*L/6]
    for (int i = N_space / 6; i <= N_space / 3; i++)
    {
        for (int j = N_space / 6; j <= N_space / 3; j++)
        {
            F(i, j) = elt;
        }
    }
    // [4L/6; 5L/6] x [L/6; 2*L/6]
    for (int i = N_space / 6; i <= N_space / 3; i++)
    {
        for (int j = 2 * N_space / 3; j <= 5 * N_space / 6; j++)
        {
            F(i, j) = elt;
        }
    }
    // [L/6; 2*L/6] x [4L/6; 5L/6]
    for (int i = 2 * N_space / 3; i <= 5 * N_space / 6; i++)
    {
        for (int j = N_space / 6; j <= N_space / 3; j++)
        {
            F(i, j) = elt;
        }
    }
    // [4L/6; 5L/6] x [4L/6; 5L/6]
    for (int i = 2 * N_space / 3; i <= 5 * N_space / 6; i++)
    {
        for (int j = 2 * N_space / 3; j <= 5 * N_space / 6; j++)
        {
            F(i, j) = elt;
        }
    }

    Matrix F_col(N_space * N_space, 1);
    for (int j = 1; j <= N_space; j++)
    {
        for (int i = 1; i <= N_space; i++)
        {
            F_col((j - 1) * N_space + i, 1) = F(i, j);
        }
    }
    return F_col;
}

Matrix surface_evolution(const double lambda, const double rho, const double c_mat)
{
    const double coeff = delta_t / (rho * c_mat);
    const double d = lambda * coeff / pow(delta_x, 2);
    const int n = N_space * N_space;
    Matrix A(n, n);

    for (int i = 1; i <= n; i++)
    {
        A(i, i) = 1 - 4 * d;
    }
    for (int i = 1; i <= n - N_space; i++)
    {
        A(i, N_space + i) = d;
    }
    for (int i = N_space + 1; i <= n; i++)
    {
        A(i, i - N_space) = d;
    }

    Matrix F = F_surface();
    Matrix B = coeff * F;

    std::vector<Matrix> U_n;

    Matrix U_start(n, 1);
    for (int i = 1; i <= n; i++)
    {
        U_start(i, 1) = u_0; // for all x, for all y, u(t=0, x, y) = u_0
    }
    U_n.push_back(U_start);

    for (int j = 0; j < N_time; j++)
    {
        const Matrix &U_prec = U_n[j];
        Matrix U_succ(n, 1);

        for (int i = 1; i <= N_space; i++)
        {
            U_succ(i, 1) = A(i, i) * U_prec(i, 1) + A(N_space + i, i) * U_prec(N_space + i, 1);
        }
        for (int i = N_space + 1; i <= n - N_space; i++)
        {
            U_succ(i, 1) = A(i - N_space, i) * U_prec(i - N_space, 1) + A(i, i) * U_prec(i, 1) + A(i + N_space, i) * U_prec(i + N_space, 1);
        }
        for (int i = n - N_space + 1; i <= n; i++)
        {
            U_succ(i, 1) = A(i - N_space, i) * U_prec(i - N_space, 1) + A(i, i) * U_prec(i, 1);
        }

        U_succ = U_succ + B;
        for (int i = n - N_space; i <= n; i++)
        {
            U_succ(i, 1) = u_0; // Dirichlet condition (y=L)
        }
        for (int i = 1; i < N_space; i++)
        {
            U_succ((i - 1) * N_space + i, 1) = u_0; // Neumann condition (x=0)
            U_succ(i * N_space, 1) = u_0;           // Dirichlet condition (x=L)
            U_succ(i * N_space + 1, 1) = u_0;       // Neumann condition (y=0)
        }

        // Débogage
        cout << "Step " << j << ": " << U_succ(1, 1) << ", " << U_succ(n, 1) << endl;

        U_n.push_back(U_succ);
    }

    Matrix U(n, N_time);
    for (int i = 0; i < N_time; i++)
    {
        const Matrix &U_bloc = U_n[i];
        for (int k = 1; k <= n; k++)
        {
            U(k, i + 1) = U_bloc(k, 1);
        }
    }

    return U;
}
