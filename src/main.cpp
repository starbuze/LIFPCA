#include "JeuSDL.h"

int main()
{
    bool modeGraphique = true;
    if (modeGraphique)
    {
        JeuSDL jeuSDL;
        jeuSDL.Afficher_SDL();
    }
    return 0;
}