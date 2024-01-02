/**
 * \file plaque.h
 * This file implements the definition of different functions used to
 * compute the heat diffusion in a surface
 *
 * It contains 2 functions :
 * - F_plaque fills a matrix according to the function F
 * - evolution_plaque realizes the different computes for the heat diffusion
 */

#ifndef PLAQUE_H // to avoid multiple inclusions
#define PLAQUE_H

#include "matrix.h"

/**
 * \brief fills a matrix according to the function F
 * \return a matrix filled with the different value corresponding to the function F
 */
Matrix F_plaque();

/**
 * \brief realizes the different computes for the heat diffusion
 * \return a matrix of the results for each points of the bar and for different times
 */
Matrix evolution_plaque(const double lambda, const double rho, const double c_mat);

#endif