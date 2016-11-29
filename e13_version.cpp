// e13.cpp

#include <iostream>
#include <cstring>
using namespace std;

enum Couleur {ROUGE, VERT, BLEU};

class Vehicule
{
public :
    Vehicule (const char* no, Couleur coul, int pui, int nbr = 4);
    void afficher () const;
    //virtual void afficher () const;

private :
    char nom[20];
    int puiss;
    int nbRoues;
    Couleur couleur;
};

Vehicule::Vehicule (const char* no, Couleur coul, int pui, int nbr)
{
    strcpy (nom, no);
    puiss = pui;
    nbRoues = nbr;
    couleur = coul;
}

void Vehicule::afficher () const
{
    /* couleur etant de type enum l'envoi du champ couleur sur cout affiche une
     * valeur numerique => conversion en une chaine
     */
    const char* chaineCouleur;
    switch (couleur)
    {
    case ROUGE :
        chaineCouleur = "rouge";
        break;
    case BLEU :
        chaineCouleur = "bleu";
        break;
    case VERT :
        chaineCouleur = "vert";
        break;
    }

    cout << nom << ", " << chaineCouleur << ", " << puiss << " CV"
         << ", " << nbRoues << " roues" << endl;
}

class Moto : public Vehicule
{
public :
    Moto (const char* no, Couleur coul, int pui, int cyl);
    void afficher () const;

private :
    int cylin;
};

Moto::Moto (const char* no, Couleur coul, int pui, int cyl)
    : Vehicule (no, coul, pui, 2)
{
    cylin = cyl;
}

void Moto::afficher () const
{
    Vehicule::afficher();
    cout << cylin << " cm3" << endl;
}

int main ()
{
    Vehicule vehi1 ("xxx", BLEU, 10, 6);
    Vehicule vehi2 ("abcd", ROUGE, 5);
    vehi1.afficher();
    vehi2.afficher();

    Moto moto1 ("mm", VERT, 7, 1000);
    moto1.afficher();

    Vehicule* pvehi;
    Moto* pmoto;
    pvehi = &moto1;
    pmoto = &moto1;

    cout << endl << "avec un pointeur Vehicule* : " << endl;
    pvehi->afficher();

    cout << endl << "avec un pointeur Moto* : " << endl;
    pmoto->afficher();

    return 0;
}
