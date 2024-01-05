#include "headers/animation.hpp"

using namespace std;
using namespace cst;

#include <SDL2/SDL.h>
#include "headers/matrix.hpp"

void play_bar(Matrix U, SDL_Renderer *renderer)
{
    // Scaling the temperature values
    double min = u_0;
    double max = max_matrix(U);
    Matrix Ubis = scale_curve(U, min, max);

    // Creating the position vector
    Matrix pos(N_space, 1);
    for (int i = 1; i < N_space + 1; i++)
    {
        pos(i, 1) = i * WINDOW_WIDTH / N_space;
    }

    // Loop for displaying temperature evolution frames
    for (int i = 0; i < t_val; i++)
    {
        // Displaying the background grid
        grid(renderer);

        // Displaying the temperature curves on the bar
        for (int j = 1; j < N_space; j++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, pos(j, 1), 400 - Ubis(j, (i + 1) * 10), pos(j + 1, 1), 400 - Ubis(j + 1, (i + 1) * 10));

            // Cokloring rectangles according to the temperature value
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

        // Rendering and clearing the frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        // Delay for visibility
        SDL_Delay(160);
    }
    // Additional delay for the final frame
    SDL_Delay(3000);
}

void play_surface(Matrix U, SDL_Renderer *renderer)
{
    for (int i = 1; i <= N_space; i++)
    {
        // Extracting temperature data for each column at position i
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
        // Displaying the temperature evolution for the extracted column
        play_bar(Ucol, renderer);
    }
}

Matrix scale_curve(Matrix U, double min, double max)
{
    // Calculate the scaling factor
    double scale = 380 / (max - min);
    for (int i = 1; i < N_space; i++)
    {
        for (int j = 1; j < N_time; j++)
        {
            // Scale each temperature value within the specified range
            double valeur = U(i, j);
            U(i, j) = scale * (valeur - min);
        }
    }
    // Return the scaled temperature matrix
    return U;
}

SDL_Window *Init_window(int width, int height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw "SDL n'a pas pu être initialisé";
    }

    // Create the window
    SDL_Window *window = SDL_CreateWindow(
        "Diffusion de la chaleur",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    // Check if window creation is successful
    if (window == nullptr)
    {
        SDL_Quit();
        throw "La fenêtre 'window' est un pointeur nul";
    }

    return window;
}

SDL_Renderer *Init_renderer(SDL_Window *window)
{
    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        0);

    // Check if renderer creation is successful
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
        // SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                // Trigger play_bar function on key press
                play_bar(U, renderer);

                break;
            }
        }
        // Clear the renderer and set background color
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
        // SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                // Trigger play_surface function on key press
                play_surface(U, renderer);

                break;
            }
        }
        // Clear the renderer and set background color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

void refresh_display(SDL_Renderer *renderer)
{
    // Set background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Update the renderer and clear the screen
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    // Delay for a short duration to control the animation speed
    SDL_Delay(160);
}

void grid(SDL_Renderer *renderer)
{
    const int gridSize = 40;

    // Set grid color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw vertical grid lines
    for (int x = 0; x < WINDOW_WIDTH; x += gridSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT / 2);
    }

    // Draw horizontal grid lines
    for (int y = 0; y < WINDOW_HEIGHT / 2; y += gridSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    // Update the renderer to display the grid
    SDL_RenderPresent(renderer);
}


