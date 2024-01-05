/**
 * \file bar.hpp
 * This file provides the implementation of various functions dedicated to
 * computing heat diffusion in a bar
 *
 * It includes 2 functions :
 * - F_bar fills a matrix based on the function F
 * - bar_evolution executes the computations for heat diffusion in the bar
 */

#ifndef BAR_HPP // to avoid multiple inclusions
#define BAR_HPP

#include "matrix.hpp"

/**
 * \brief ills a matrix based on the function F
 * \return a matrix filled with values corresponding to the function F
 */
Matrix F_bar();

/**
 * \brief executes the computations for heat diffusion in the bar
 * \param lambda the lambda coefficient of the material
 * \param rho the rho coefficient of the material
 * \param c_mat the c coefficient of the material
 * \return a matrix containing results for each point of the bar at different time intervals
 */
Matrix bar_evolution(const double, const double, const double);

#endif