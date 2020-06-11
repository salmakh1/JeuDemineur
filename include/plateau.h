
#ifndef PLATEAU_H
#define PLATEAU_H
#include "Case.h"
#define N 100
#define M 99
#include <bits/stdc++.h>
using namespace std;
class plateau
{
    public:

        plateau();
        virtual ~plateau();
        pair<int,int> corddecouvrir();
        bool gagner();
        void verif();
       // void start();
        pair <int,int> dimcase();
        int action();
        void ajoutaufichier();

        int nbminevoisine(int i,int j);
        void afficher();

        void remplissage();
        void repaction();
        //void affichercont();
        void repsuraction(pair<int, int> k );
        void decouvrirx(int x ,int y );
        void affichage();
        bool ingrid (int i,int j);
    protected:
        int longueur,largeur;
        int cm,cc,nbmin;
        Case c [N][M];
        int gameover;
    private:
};

#endif // PLATEAU_H
