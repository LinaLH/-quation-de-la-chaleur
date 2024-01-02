/**
 * \file interface.hpp
 * This file implements the definition of different functions used to
 * interact with the user
 *
 * It contains 2 functions :
 * - support_choice returns the choice of support made by the user
 * - material_choice returns the choice of material made by the user
 */

#ifndef INTERFACE_HPP // to avoid multiple inclusions
#define INTERFACE_HPP

/**
 * \brief returns the choice of support made by the user
 * \return an integer corresponding to the choosen support: 1 for the bar and 2 for the surface
 */
int support_choice();

/**
 * \brief returns the choice of material made by the user
 * \return an integer corresponding to the choosen material: 1 for the copper, 2 for iron, 3 for glass and 4 for polystyren
 */
int material_choice();

#endif