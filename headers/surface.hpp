/**
 * \file surface.hpp
 * This file provides the implementation of various functions dedicated to
 * computing heat diffusion in a surface
 *
 * It includes 2 functions :
 * - F_surface fills a matrix based on the function F
 * - surface_evolution executes the computations for heat diffusion in the surface
 */

#ifndef SURFACE_HPP // to avoid multiple inclusions
#define SURFACE_HPP

#include "matrix.hpp"

/**
 * \brief ills a matrix based on the function F
 * \return a matrix filled with values corresponding to the function F
 */
Matrix F_surface();

/**
 * \brief executes the computations for heat diffusion in the surface
 * \param lambda the lambda coefficient of the material
 * \param rho the rho coefficient of the material
 * \param c_mat the c coefficient of the material
 * \return a matrix containing results for each point of the surface at different time intervals
 */
Matrix surface_evolution(const double lambda, const double rho, const double c_mat);

#endif