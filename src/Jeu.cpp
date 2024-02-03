
#include <iostream>
#include <stdlib.h>
#include "Jeu.h"

using namespace std;

char terrain[10][10];

char terrain2[10][10];

Jeu::Jeu()
{
    initialiseTerrain();
}

void Jeu::CopierTableau(char envoyeur[10][10], char destination[10][10])
{
    for(int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            destination[i][j] = envoyeur[i][j];
        }
    }
}



void Jeu::VerifierSiMaison()
{
    CopierTableau(terrain , terrain2);
    for(int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            if(terrain2[i][j] == '.')
            {
                terrain2[i][j] = '#';
                int ligne = 0;
                int colonne = 0;
                while(terrain2[ligne][colonne] != '.' && terrain2[ligne][colonne] != 'R')
                {
                    if(ligne == 9)
                    {
                        ligne = -1;
                        colonne++;
                    }
                    ligne++;
                }
                int AireDeJeu = CalculerAireDeJeu(ligne , colonne); 
                cout<<AireDeJeu<<endl;
                if(AireDeJeu < 100)
                {
                    terrain[i][j] = 'R'; //Si l'air est differente de 100 alors la maison a bloquer l'acces a une case donc on met une route
                }
            }
            CopierTableau(terrain , terrain2);
        }
    }
    CopierTableau(terrain2 , terrain);
    for(int k = 0 ; k < 10 ; k++)
    {
        for(int l = 0 ; l < 10 ; l++)
        {
            cout<<terrain[k][l];
        }
        cout<<endl;
    }
}

int Jeu::CalculerAireDeJeu(int x , int y)
{
    int AireDeJeu = 0;
    if(x >= 0 && x < 10 && y >= 0 && y < 10)
    {
        if(terrain2[x][y] == '.')
        {
            terrain2[x][y] = ',';
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x-1 , y);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x+1 , y);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x , y-1);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x , y+1);
            AireDeJeu = AireDeJeu + 1;
        }
        else if(terrain2[x][y] == 'R')
        {
            terrain2[x][y] = 'M';
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x-1 , y);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x+1 , y);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x , y-1);
            AireDeJeu = AireDeJeu + CalculerAireDeJeu(x , y+1);
            AireDeJeu = AireDeJeu + 1;
        }
        else if(terrain2[x][y] == '#')
        {
            terrain2[x][y] = '%';
            AireDeJeu = AireDeJeu + 1;
        }
    }
    return AireDeJeu;
}

void Jeu::initialiseTerrain()
{
    for (int i = 0; i < 10; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            terrain[i][j] = '.';
        }
    }
}