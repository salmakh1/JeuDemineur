#include <fstream>
#include "plateau.h"
#include "Case.h"
#include <bits/stdc++.h>
int di[8]={-1,-1,-1,0,0,1,1,1};
int dj[8]={0,-1,1,-1,1,1,-1,0};
using namespace std ;
plateau::plateau()
{
    cc=0;
    gameover=0;
    int i;
    cout<<"donnez la dimension voulue: "<<endl<<"1) si 9*9 "<<endl<<"2) si 16*16 "<<endl<<"3) si 16*30"<<endl;
    cin>>i;
    if (i==1)
        {
            longueur=9;
            largeur=9;
            nbmin=10;
            cm=10;
        }
    else if (i==2)
        {
            longueur=16;
            largeur=16;
            nbmin=40;
            cm=40;
        }
    else if (i==3)
        {
            longueur=16;
            largeur=30;
            nbmin=99;
            cm=99;
        }
}
//fonction pour le remplissage de la matrice
void plateau :: remplissage()
{
    srand(time(0));
    pair <int,int> h= make_pair(longueur, largeur) ;
    int k=0;
    while ( k < nbmin)
    {
        int i= rand()% h.first ;
        int j= rand()% h.second ;
        if (c[i][j].contenu!='M')
        {
            c[i][j].contenu='M' ;
            k++;
        }
    }
    for (int i=0; i<h.first; i++)
    {
        for (int j=0; j<h.second; j++)
        {
            if (c[i][j].contenu!='M')
            {
                if (nbminevoisine(i,j) != 0)
                    c[i][j].contenu= '0'+nbminevoisine(i,j);
                else
                    c[i][j].contenu= 'X';

            }
        }
    }
}
/*void plateau ::affichercont ()
{       pair <int,int> h= make_pair(longueur, largeur) ;
     for (int i=0; i<h.first; i++)
    {
        for (int j=0; j<h.second; j++)
        {
            cout<<c[i][j].contenu;
        }
        cout<<endl;
    }
}*/

//extraire la dimension de la matrice
pair <int,int> plateau::dimcase()
    {
        return make_pair(longueur , largeur);
    }
plateau::~plateau()
{
    //dtor
}

//decouvrir les coordonnées dont on veut effectuer une action
pair<int,int> plateau::corddecouvrir()
{   int n,m;
    cout<<"decouvrez une case de votre choix en precisant "<<endl<<"son numero de ligne et son numero de colonne"<<endl;
    cin>>n>>m;

    return(make_pair(n,m));
}

//donner l'action qu'on veut effectuer sur la case choisie
int plateau:: action()
{
    int a;
    bool b=false;
    while (b==false)
        {
            cout<<"entrez une action que vous voulez effectuer:"<<endl<<"1) si vous voulez la decouvrir "<<endl<<"2) si vous voulez la marquer"<<endl<<"3) si vous voulez la demarquer"<<endl;
            cin>>a;
            if ((a>3)||(a<0))
            {
                cout<<"vous devez entrez un nombre entre 1 et 3"<<endl;
                b=false;
            }
            else
                b=true;
    }
    return (a);

}

//verifier si les coordpnnées appartiennet à la matrice
bool plateau :: ingrid (int i,int j)
{
    pair <int,int> k=dimcase();
    if ((i>=0)&&(j>=0)&&(i<k.first)&&(j<k.second))
        return(true);
    else
        return(false);
}


//fonction reccursive qui permet d'afficher les cases s'il s'agit d'un blanc
void plateau::decouvrirx(int i,int j)
{
    if((c[i][j].contenu!='X')&&(c[i][j].contenu!='M')&&(c[i][j].etat=="couverte"))
    {
        c[i][j].etat="decouverte";
    }
    else if((c[i][j].contenu=='X')&&(c[i][j].etat=="couverte"))
       {
           c[i][j].etat="decouverte";
           for(int k=0;k<8;k++){
            if (ingrid(i + di[k], j + dj[k]))
                decouvrirx(i + di[k], j + dj[k]);


           }
       }
}

//effectuer une action
void plateau::repsuraction(pair<int, int> k )
{

    if (c[k.first][k.second].contenu=='M')
        {
            c[k.first][k.second].etat="couverte";
            cout<<"vous avez perdu"<<endl;
            gameover=1;
            exit(0);
        }
    else if(c[k.first][k.second].contenu=='X')
        {
            decouvrirx(k.first,k.second);
        }
}



//selon le choix de l'action on change l'etat
void plateau::repaction()
{
    int choix = action();
    pair<int,int> k= corddecouvrir();
    system("cls");
    //cout << choix << k.first << k.second << endl;
    if (choix==1)
    {
        if (c[k.first][k.second].etat == "couverte")
        {
            if ((c[k.first][k.second].contenu!='M') && (c[k.first][k.second].contenu!='X'))
            {
                cc++;
                c[k.first][k.second].etat="decouverte" ;
            }
            else

            {repsuraction(k);
            cc++;
            c[k.first][k.second].etat="decouverte" ;

            }
        }
        else if (c[k.first][k.second].etat == "decouverte")
            cout << "la case est deja decouverte!"<<endl;
        else if (c[k.first][k.second].etat == "marquee")
            cout << "la case est deja marquee!"<<endl;
    }
    else if (choix==2)
    {
        if (c[k.first][k.second].etat == "couverte")
        {
            cc++;
            cm--;
            c[k.first][k.second].etat="marquee" ;
        }
        else if (c[k.first][k.second].etat == "decouverte")
            cout << "la case est deja decouverte!"<<endl;
        else
            cout << "la case est deja marquee!"<<endl;
    }
    else
    {
        if (c[k.first][k.second].etat == "marquee")
        {
            cc++;
            cm++;
            c[k.first][k.second].etat="couverte" ;
        }
        else if (c[k.first][k.second].etat == "decouverte")
            cout << "la case est deja decouverte!"<<endl;
        else
            cout << "la case est deja couverte!"<<endl;
    }

    verif();
}

//compter le nombre de mine voisines à chaque case
int plateau::nbminevoisine(int i,int j)
{
    int nb=0;
            if(ingrid (i-1,j)&&c[i-1][j].contenu=='M')
                nb++;
            if (ingrid (i-1,j-1)&&c[i-1][j-1].contenu=='M')
                nb++;
            if (ingrid (i-1,j+1)&&c[i-1][j+1].contenu=='M')
                nb++;
            if (ingrid (i,j-1)&&c[i][j-1].contenu=='M')
                nb++;
            if (ingrid (i,j+1)&&c[i][j+1].contenu=='M')
                nb++;
            if (ingrid (i+1,j)&&c[i+1][j].contenu=='M')
                nb++;
            if (ingrid (i+1,j-1)&&c[i+1][j-1].contenu=='M')
                nb++;
            if (ingrid (i+1,j+1)&&c[i+1][j+1].contenu=='M')
                nb++;
    return (nb);
}

//affichage de la matrice
void plateau::affichage()
{

    pair <int,int> d = dimcase();
        cout<<endl;
    cout<<"                                               ----------------------"<<endl;
    cout<<"                                                  JEU DE DEMINEUR "<<endl;
    cout<<"                                               ----------------------"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                                                   ";
    for(int i=0;i<d.second;i++)
        {
            cout<<i<<" ";
        }

    cout<<endl;


    for(int i=0;i<d.first;i++)
    {   cout<<"                                                "<<i <<" ";
        for(int j=0;j<d.second;j++)
        {
            if (c[i][j].etat=="couverte")
                {cout<<" #";
                }
            else if(c[i][j].etat=="decouverte")
                cout<< " "<<c[i][j].contenu;
            else if(c[i][j].etat=="marquee")
                  cout<<" D";
        }
        cout<<endl;
        cout<<"                                                  "<<"-------------------"<<endl;
    }
    cout<<endl;
    cout<<"nbr de cout= "<<cc<<endl;
    cout<<"nbr de mine restant= "<<cm<<endl;
}

//verifier si l'utilisateur a gagne
bool plateau :: gagner()
{
    pair <int,int> d = dimcase();
    int b;
    int a=0;
    for (int i=0; i<d.first; i++)
    {
         for (int j=0; j<d.second; j++)
         {
             if ((c[i][j].contenu=='M')&&(c[i][j].etat=="marquee"))
                a++;
             else if ((c[i][j].contenu!='M')&&(c[i][j].contenu!='D')&&(c[i][j].etat=="decouverte"))
                a++;
        }
    }
    b = d.first * d.second ;
    //cout << a << " " << b << endl;
    if (a==b)
        return (true) ;
    return false;

}


//ajout au fichier le score et le nom
void plateau :: ajoutaufichier ()
{
    ofstream fichier("test.txt", ios::app );
    if (fichier)
    {   string nom,score;
        cout << "Donnez votre nom" << endl ;
        cin >> nom ;
        fichier << nom << " " << cc << endl;
        fichier.close();
    }

}

//effectuer l'ajout au fichier dans le cas qu'il gagne et sortir s'il a perdu
void plateau :: verif()
{   bool b=gagner();
    if (gameover==1)
    {
        cout << "vous avez perdu"<< endl;
        exit(0);
    }
    else if (b==true)
    {
        cout << "vous avez gagne"<< endl;
        ajoutaufichier();
        exit(0);
    }

}
/*void plateau:: start()
{
  remplissage();
    while ((gameover==0)&&(gagner()==false))
    {
       affichage();
        repaction();

    }
}*/
