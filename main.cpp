#include "headers/matrix.hpp"
#include "headers/constants.hpp"
#include "headers/interface.hpp"
#include "headers/materiel.hpp"
#include "headers/animation.hpp"
#include "headers/barre.hpp"
#include "headers/plaque.hpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;
using namespace cst;
using namespace materiaux;

int main()
{
    int support = support_choice();

    int materiel = material_choice();
    double lambda, rho, c_mat;
    if (materiel == 1)
    {
        lambda = cuivre::lambda;
        rho = cuivre::rho;
        c_mat = cuivre::c_mat;
    }
    if (materiel == 2)
    {
        lambda = fer::lambda;
        rho = fer::rho;
        c_mat = fer::c_mat;
    }
    if (materiel == 3)
    {
        lambda = verre::lambda;
        rho = verre::rho;
        c_mat = verre::c_mat;
    }
    if (materiel == 4)
    {
        lambda = polystyrene::lambda;
        rho = polystyrene::rho;
        c_mat = polystyrene::c_mat;
    }

    Matrix U(N_space, N_space);

    if (support == 1)
    {
        Matrix U = evolution_barre(lambda, rho, c_mat);
        cout << U << endl;
        SDL_Window *window = Init_window(WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_Renderer *renderer = Init_renderer(window);
        loop_bar(renderer, U);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if (support == 2)
    {
        Matrix U = evolution_plaque(lambda, rho, c_mat);
        cout << U << endl;
        SDL_Window *window = Init_window(WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_Renderer *renderer = Init_renderer(window);
        loop_surface(renderer, U);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}
