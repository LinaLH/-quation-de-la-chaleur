#include "headers/animation.h"

using namespace std;
using namespace cst;

void play_bar(Matrix U, SDL_Renderer *renderer)
{
    // Ajouter ces lignes pour dessiner un rectangle rouge
    SDL_Rect rect;
    rect.x = 100; // ajustez la position x selon vos besoins
    rect.y = 100; // ajustez la position y selon vos besoins
    rect.w = 200; // ajustez la largeur selon vos besoins
    rect.h = 150; // ajustez la hauteur selon vos besoins

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    double min = u_0;
    double max = max_matrix(U);
    Matrix Ubis = scale_curve(U, min, max);
    Matrix pos(N_space, 1);
    for (int i = 1; i < N_space + 1; i++)
    {
        pos(i, 1) = i * WINDOW_WIDTH / N_space;
    }

    for (int i = 0; i < t_val; i++)
    {
        grid(renderer);
        for (int j = 1; j < N_space; j++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, pos(j, 1), 400 - Ubis(j, (i + 1) * 10), pos(j + 1, 1), 400 - Ubis(j + 1, (i + 1) * 10));
            double val = U(j, (i + 1) * 10);
            double qte = 1 - (max - val) / (max - min);

            SDL_Rect rect;
            rect.x = 119.5 + j;
            rect.y = 600;
            rect.w = 1;
            rect.h = 25;
            if (qte <= 0.25)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0 + qte * 1020, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }

            if (qte >= 0.25 && qte <= 0.5)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 255 - (qte - 0.25) * 1020, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }
            if (qte >= 0.5 && qte <= 0.75)
            {
                SDL_SetRenderDrawColor(renderer, 0 + (qte - 0.5) * 1020, 255, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }
            if (qte >= 0.75)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255 - (qte - 0.75) * 1020, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(160);
    }
    SDL_Delay(3000);
}

void play_surface(Matrix U, SDL_Renderer *renderer)
{
    for (int i = 1; i <= N_space; i++)
    {

        Matrix Ucol(N_space, N_time);
        cout << "i" << i << endl;
        for (int k = 1; k <= N_space; k++)
        {
            for (int j = 1; j <= N_time; j++)
            {
                Ucol(k, j) = U((i - 1) * N_space + k, j);
                cout << "j" << j << endl;
            }
            cout << "k" << k << endl;
        }

        play_bar(Ucol, renderer);
    }
}

Matrix scale_curve(Matrix U, double min, double max)
{
    double scale = 380 / (max - min);
    for (int i = 1; i < N_space; i++)
    {
        for (int j = 1; j < N_time; j++)
        {
            double valeur = U(i, j);
            U(i, j) = scale * (valeur - min);
        }
    }
    return U;
}

SDL_Window *Init_window(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw "SDL n'a pas pu être initialisé";
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow(
        "Diffusion de la chaleur",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        SDL_Quit();
        throw "La fenêtre 'window' est un pointeur nul";
    }

    return window;
}

SDL_Renderer *Init_renderer(SDL_Window *window)
{
    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        0);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw "Le renderer est un pointeur nul";
    }

    return renderer;
}

void loop_bar(SDL_Renderer *renderer, Matrix U)
{
    bool running = true;
    while (running)
    {
        // Événements de la SDL
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {

                play_bar(U, renderer);

                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

void loop_surface(SDL_Renderer *renderer, Matrix U)
{
    bool running = true;
    while (running)
    {
        // Événements de la SDL
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {

                play_surface(U, renderer);

                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

void refreshAnim(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Delay(160);
}

void grid(SDL_Renderer *renderer)
{
    const int gridSize = 40;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
    for (int x = 0; x < WINDOW_WIDTH; x += gridSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT / 2);
    }
    for (int y = 0; y < WINDOW_HEIGHT / 2; y += gridSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
    SDL_RenderPresent(renderer);
}

double max_matrix(Matrix U)
{
    double max = 0;
    for (int i = 1; i < N_space + 1; i++)
    {
        for (int j = 1; j < 101; j++)
        {
            if (U(i, j * 10) > max)
                max = U(i, j * 10);
        }
    }
    return max;
}
