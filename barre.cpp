#include "headers/barre.h"
#include "headers/matrix.h"
#include "headers/constants.h"

#include <cmath>

using namespace cst;

Matrix F_barre()
{
    Matrix F(N_space, 1);
    // [L/10; 2*L/10]
    for (int p = N_space / 10; p <= N_space / 5; p++)
    {
        F(p, 1) = tmax * pow(f, 2);
    }
    // [5L/10; 6L/10]
    for (int p = N_space / 2; p <= 3 * N_space / 5; p++)
    {
        F(p, 1) = tmax * pow(f, 2) * 0.75;
    }
    return F;
}

Matrix evolution_barre(const double lambda, const double rho, const double c_mat)
{
    const double kappa = lambda / (rho * c_mat);
    const double alpha = kappa * delta_t / pow(delta_x, 2);
    const double a = -alpha;
    const double b = 1 + 2 * alpha;
    Matrix A(N_space, N_space);
    fill_tridiag(A, a, b, a);

    Matrix F = F_barre();
    Matrix C = -alpha * pow(delta_x, 2) * F / lambda;

    Matrix Id(N_space, N_space);
    fill_tridiag(Id, 0, 1, 0);
    Matrix A_inv = inverse(N_space, a, b, Id);

    Matrix E = A_inv * C;

    Matrix U = Matrix(N_space, N_time);
    for (int i = 1; i <= N_space; i++)
        U(i, 1) = u_0; // for all x, u(t=0, x) = u_0
    for (int j = 1; j <= N_time; j++)
    {
        U(1, j) = u_0;       // Neumann condition (x=0)
        U(N_space, j) = u_0; // Dirichlet condition (x=L)
    }
    for (int i = 1; i < N_time; i++)
    {
        Matrix Ucol(N_space, 1);
        for (int k = 1; k <= N_space; k++)
        {
            Ucol(k, 1) = U(k, i);
        }
        Matrix passage = A_inv * Ucol - E;
        for (int j = 1; j <= N_space; j++)
        {
            if (j == 2)
                U(j, i + 1) = U(j - 1, i + 1);
            if (U(j, i + 1) == 0.0)
                U(j, i + 1) = passage(j, 1);
            if (U(j, i + 1) < 286.15)
                U(j, i + 1) = 286.15;
        }
    }
    return U;
}
