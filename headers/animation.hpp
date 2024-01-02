/**
 * \file animation.hpp
 * This file implements the definition of different functions used to
 * display animation
 *
 * It contains 8 functions :
 * - play_bar allows to display the colored animation and the curve for the bar
 * - Init_window allows to initialize the window for the SDL library
 * - Init_renderer allows to initialize the renderer for the SDL library
 * - loopAnim manages the loop used with SDL to show the animation
 * - grid displays a grid behind the curve
 * - max_matrix returns the maximum value of the matrix
 * - refresh_display refreshes the display
 * - scale_curve changes the value of the matrix for the display of the curve
 */

#include <SDL2/SDL.h>
#include "matrix.hpp"
#include "constants.hpp"

/**
 * \brief displays the colored animation and the curve for the bar
 * \param U the matrix in which we take the value to display
 * \param renderer the renderer initialized for SDL
 */
void play_bar(Matrix U, SDL_Renderer *renderer);

/**
 * \brief displays the colored animation and the curve for the surface
 * \param U the matrix in which we take the value to display
 * \param renderer the renderer initialized for SDL
 */
void play_surface(Matrix U, SDL_Renderer *renderer);

/**
 * \brief initializes the window fot the SDL library
 * \param width the width we want for the window
 * \param height the height we want for the window
 * \return a window initialized for SDL
 */
SDL_Window *Init_window(int width, int height);

/**
 * \brief initializes the renderer for the SDL library
 * \param window the window previously initialized
 * \return a renderer initialized for SDL
 */
SDL_Renderer *Init_renderer(SDL_Window *window);

/**
 * \brief manages the loop used with SDL to show the animation
 * \param renderer the renderer initialized
 * \param U the matrix in which we take the value to display
 */
void loop_bar(SDL_Renderer *renderer, Matrix U);

/**
 * \brief manages the loop used with SDL to show the animation
 * \param renderer the renderer initialized
 * \param U the matrix in which we take the value to display
 */
void loop_surface(SDL_Renderer *renderer, Matrix U);

/**
 * \brief displays the grid behind the curve
 * \param renderer the renderer initialized
 */
void grid(SDL_Renderer *renderer);

/**
 * \brief returns the maximum value of the matrix
 * \param U the matrix in which we search for the maximum value
 * \return a double corresponding to the maximum value of the matrix
 */
double max_matrix(Matrix U);

/**
 * \brief refreshes the display
 * \param renderer the renderer we want to refresh
 */
void refresh_display(SDL_Renderer *renderer);

/**
 * \brief changes the value of the matrix for the display of the curve
 * \param U the matrix we want to scale
 * \param min the minimum value of the matrix
 * \param max the maximum value of the matrix
 * \return the matrix scaled
 */
Matrix scale_curve(Matrix U, double min, double max);
