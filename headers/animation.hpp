/**
 * \file animation.hpp
 * This file provides the implementation of various functions dedicated to
 * rendering animations.
 *
 * It encompasses 8 functions:
 * - play_bar: Displays a colored animation along with the curve for the bar.
 * play_surface: Displays a colored animation and the curve for the surface.
 * - Init_window: Initializes the window for the SDL library.
 * - Init_renderer: Initializes the renderer for the SDL library.
 * - loop_bar: Handles the SDL loop responsible for showcasing the animation (for the bar).
 * - loop_surface : Handles the SDL loop responsible for showcasing the animation (for the surface).
 * - grid: Renders a grid as a backdrop behind the curve.
 * - max_matrix: Returns the maximum value within the matrix.
 * - refresh_display: Updates and refreshes the display.
 * - scale_curve: Adjusts the matrix value for curve visualization.
 */

#include <SDL2/SDL.h>
#include "matrix.hpp"
#include "constants.hpp"

/**
 * \brief displays a colored animation along with the curve for the bar
 * \param U the matrix from which we extract the value for display
 * \param renderer the renderer set up for SDL
 */
void play_bar(Matrix U, SDL_Renderer *renderer);

/**
 * \brief displays a colored animation and the curve for the surface
 * \param U the matrix from which we extract the value for display
 * \param renderer the renderer set up for SDL
 */
void play_surface(Matrix U, SDL_Renderer *renderer);

/**
 * \brief initializes the window fot the SDL library
 * \param width the desired width for the window
 * \param height the desired height for the window
 * \return an SDL-initialized window
 */
SDL_Window *Init_window(int width, int height);

/**
 * \brief initializes the renderer for the SDL library
 * \param window the previously initialized window
 * \return an SDL-initialized renderer
 */
SDL_Renderer *Init_renderer(SDL_Window *window);

/**
 * \brief handles the SDL loop responsible for showcasing the animation (for the bar)
 * \param renderer the initialized renderer
 * \param U the matrix from which we extract the value for display
 */
void loop_bar(SDL_Renderer *renderer, Matrix U);

/**
 * \brief handles the SDL loop responsible for showcasing the animation (for the sirface)
 * \param renderer the initialized renderer
 * \param U the matrix from which we extract the value for display
 */
void loop_surface(SDL_Renderer *renderer, Matrix U);

/**
 * \brief renders a grid as a backdrop behind the curve
 * \param renderer the initialized renderer
 */
void grid(SDL_Renderer *renderer);

/**
 * \brief returns the maximum value within the matrix
 * \param U the matrix in which we search for the maximum value
 * \return a double representing the maximum value in the matrix
 */
double max_matrix(Matrix U);

/**
\brief Updates and refreshes the display.
\param renderer The renderer we want to refresh.
*/
void refresh_display(SDL_Renderer *renderer);

/**
 * \brief adjusts the matrix values for optimal curve representation
 * \param U the matrix to be adjusted
 * \param min the minimum value in the matrix
 * \param max the maximum value in the matrix
 * \return the scaled matrix
 */
Matrix scale_curve(Matrix U, double min, double max);
