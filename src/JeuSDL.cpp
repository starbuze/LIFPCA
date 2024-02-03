#include "JeuSDL.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

JeuSDL::JeuSDL()
{
}

void JeuSDL::Afficher_SDL()
{
    SDL_Window *window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Init(SDL_INIT_VIDEO);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    plaine = IMG_LoadTexture(renderer, "./data/plaine_blanche.png");
    batiment = IMG_LoadTexture(renderer, "./data/batiment.png");
    route1 = IMG_LoadTexture(renderer, "./data/route_milieu.png");
    route2 = IMG_LoadTexture(renderer, "./data/route_cote.png");


    SDL_Event event;

    bool quit = false;
    while (!quit)
    {
        Afficher_Terrain_Complet_SDL();
        SDL_RenderPresent(renderer);

        // Gestion des événements
        
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: // L'utilisateur a cliqué sur la croix en haut à droite de la fenêtre
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if(jeu.terrain[(int)(mouseX/100)][(int)(mouseY/100)] == '.')
                {
                    jeu.terrain[(int)(mouseX/100)][(int)(mouseY/100)] = '#';
                    jeu.VerifierSiMaison();
                }

            }
            break;
            }
        }
    }
}

void JeuSDL::Afficher_Terrain_Complet_SDL()
{
    rect.h = WINDOW_HEIGHT / nbBlocs;
    rect.w = WINDOW_WIDTH / nbBlocs;
    for (int i = 0; i < nbBlocs; i++)
    {
        rect.x = i * rect.h;

        for (int j = 0; j < nbBlocs; j++)
        {
            rect.y = j * rect.w;

            Afficher_Bloc_SDL(jeu.terrain[i][j] , i , j);
        }
    }
}

void JeuSDL::Afficher_Bloc_SDL(char _bloc , int x , int y)
{
    switch (_bloc)
    {
    case '#':
        SDL_RenderCopy(renderer, batiment, NULL, &rect);
        break;
    case '.':
        SDL_RenderCopy(renderer, plaine, NULL, &rect);
        break;
    case 'R' :
        SDL_RenderCopy(renderer, route1, NULL, &rect);
        Poser_route(x , y);
        break;
    }
}

void JeuSDL::Poser_route(int x , int y)
{
    if(x != 0)
    {
        if(jeu.terrain[x-1][y] == 'R')
        {
            SDL_RenderCopy(renderer, route2, NULL, &rect);
            rect.x = (x-1) * rect.w;
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 180, NULL, SDL_FLIP_NONE);
            rect.x = x * rect.w;
        }
    }
    if(x != 9)
    {
        if(jeu.terrain[x+1][y] == 'R')
        {
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 180, NULL, SDL_FLIP_NONE);
            rect.x = (x+1) * rect.w;
            SDL_RenderCopy(renderer, route2, NULL, &rect);
            rect.x = x * rect.w;
        }
    }
    if(y != 0)
    {
        if(jeu.terrain[x][y-1] == 'R')
        {
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
            rect.y = (y-1) * rect.w;
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            rect.y = y * rect.w;
        }
    }
    if(y != 9)
    {
        if(jeu.terrain[x][y+1] == 'R')
        {
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
            rect.y = (y+1) * rect.w;
            SDL_RenderCopyEx(renderer, route2, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
            rect.y = y * rect.w;
        }
    }
}

