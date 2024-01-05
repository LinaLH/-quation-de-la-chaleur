#include "headers/matrix.hpp"
#include "headers/constants.hpp"
#include "headers/interface.hpp"
#include "headers/material.hpp"
#include "headers/animation.hpp"
#include "headers/bar.hpp"
#include "headers/surface.hpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;
using namespace cst;
using namespace materials;

int main()
{

    // cout << "Beggining of the program" << endl;
    int support = support_choice();
    // cout << "Choice of the support done" << endl;
    int material = material_choice();
    // cout << "Choice of the constants done" << endl;
    double lambda, rho, c_mat;
    if (material == 1)
    {
        lambda = cuivre::lambda;
        rho = cuivre::rho;
        c_mat = cuivre::c_mat;
        // cout << "Copper loop done" << endl;
    }
    if (material == 2)
    {
        lambda = fer::lambda;
        rho = fer::rho;
        c_mat = fer::c_mat;
        // cout << "Iron loop done" << endl;
    }
    if (material == 3)
    {
        lambda = verre::lambda;
        rho = verre::rho;
        c_mat = verre::c_mat;
        // cout << "Glass loop done" << endl;
    }
    if (material == 4)
    {
        lambda = polystyrene::lambda;
        rho = polystyrene::rho;
        c_mat = polystyrene::c_mat;
        // cout << "Polystyrene loop done" << endl;
    }

    Matrix U(N_space, N_space);
    // cout << "Matrix created" << endl;
    if (support == 1)
    {
        // cout << "Beginning of the curl" << endl;
        Matrix U = bar_evolution(lambda, rho, c_mat);
        // cout << "Bar evolution don" << endl;
        cout << U << endl;
        SDL_Window *window = Init_window(WINDOW_WIDTH, WINDOW_HEIGHT);
        // cout << "sdl window done" << endl;
        SDL_Renderer *renderer = Init_renderer(window);
        // cout << "sdl renderer done" << endl;
        loop_bar(renderer, U);
        // cout << "loop bar done" << endl;
        SDL_DestroyRenderer(renderer);
        // cout << "destroy renderer done" << endl;
        SDL_DestroyWindow(window);
        // cout << "destroy window done" << endl;
        SDL_Quit();
        // cout << "quit done" << endl;
    }

    if (support == 2)
    {
        Matrix U = surface_evolution(lambda, rho, c_mat);
        // cout << "Surface evolution done" << endl;
        // cout << U << endl;
        SDL_Window *window = Init_window(WINDOW_WIDTH, WINDOW_HEIGHT);
        // cout << "sdl window done" << endl;
        SDL_Renderer *renderer = Init_renderer(window);
        // cout << "sdl renderer done" << endl;
        loop_surface(renderer, U);
        // cout << "loop surface done" << endl;
        SDL_DestroyRenderer(renderer);
        // cout << "destroy renderer done" << endl;
        SDL_DestroyWindow(window);
        // cout << "destroy window done" << endl;
        SDL_Quit();
        // cout << "quit done" << endl;
    }

    return 0;
}
