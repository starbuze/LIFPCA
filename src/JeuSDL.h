#ifndef _JeuSDL_
#define _JeuSDL_
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Jeu.h"

class JeuSDL
{
    private :

    #define WINDOW_WIDTH 1000
    #define WINDOW_HEIGHT 1000
    SDL_Renderer *renderer;
    SDL_Rect rect;
    SDL_Texture *plaine;
    SDL_Texture *batiment;
    SDL_Texture *route1;
    SDL_Texture *route2;
    Jeu jeu;

    public:

    const int nbBlocs = 10;
    
    JeuSDL();

    void Afficher_SDL();

    void Afficher_Bloc_SDL(char _bloc , int x , int y);

    void Afficher_Terrain_Complet_SDL();

    void Poser_route(int x , int y);
};
#endif
