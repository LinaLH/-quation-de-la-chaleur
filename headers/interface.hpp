/**
 * \file interface.hpp
 * This file provides the implementation of various functions for
 * user interaction
 *
 * It contains 2 functions :
 * - support_choice returns the user's choice of support
 * - material_choice returns the user's choice of material
 */

#ifndef INTERFACE_HPP // to avoid multiple inclusions
#define INTERFACE_HPP

/**
 * \brief returns the user's choice of support
 * \return an integer representing the selected support : 1 for the bar and 2 for the surface
 */
int support_choice();

/**
 * \brief returns the user's choice of material
 * \return an integer representing the selected material : 1 for copper, 2 iron, 3 for glass and 4 for polystyren
 */
int material_choice();

#endif