#ifndef _Jeu_
#define _Jeu_

class Jeu
{
private:

public:
    Jeu();
    void CopierTableau(char tab[10][10] , char tab2[10][10]);
    void VerifierSiMaison();
    int CalculerAireDeJeu(int x , int y);
    char terrain[10][10];
    void initialiseTerrain();
    void DetectionGouleau();
};

#endif