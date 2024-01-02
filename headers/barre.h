/**
 * \file barre.h
 * This file implements the definition of different functions used to
 * compute the heat diffusion in a bar
 *
 * It contains 2 functions :
 * - F_barre fill a matrix according to the function F
 * - evolution_barre realize the different computes for the heat diffusion
 */

#ifndef BARRE_H // to avoid multiple inclusions
#define BARRE_H

#include "matrix.h"

/**
 * \brief fill a matrix according to the function F
 * \return a matrix filled with the different value corresponding to the function F
 */
Matrix F_barre();

/**
 * \brief realize the different computes for the heat diffusion
 * \param lambda the lambda coefficient of the material
 * \param rho the rho coefficient of the material
 * \param c_mat the c coefficient of the material
 * \return a matrix of the results for each points of the bar and for different times
 */
Matrix evolution_barre(const double, const double, const double);

#endif