// e15_1.cpp
// exercice E15 1ere partie

#include <iostream>
#include <cstring>
using namespace std;

class Vehicule
{
public :
    Vehicule (int nserie);
    void afficher () const;

    /* on ne doit pas pouvoir creer directement des objets Vehicule
     * => la classe Vehicule doit etre abstraite
     * => elle doit avoir une fonction virtuelle pure
     */
    virtual void f () = 0;

private :
    int numSerie;
};

Vehicule::Vehicule (int nserie)
{
    numSerie = nserie;
}

void Vehicule::afficher () const
{
    cout << "numero serie : " << numSerie << endl;
}

class Terrestre : public Vehicule
{
public :
    Terrestre (int nserie, int nbr);
    void afficher () const;

    void f () {}    // on definit f sinon la classe serait abstraite

private :
    int nbRoues;
};

Terrestre::Terrestre (int nserie, int nbr)
    : Vehicule (nserie)
{
    nbRoues = nbr;
}

void Terrestre::afficher () const
{
    Vehicule::afficher();
    cout << nbRoues << " roues" << endl;
}

class Marin : public Vehicule
{
public :
    Marin (int nserie, int tir);
    void afficher () const;

    void f () {}    // on definit f sinon la classe serait abstraite

private :
    int tirant;
};

Marin::Marin (int nserie, int tir)
    : Vehicule (nserie)
{
    tirant = tir;
}

void Marin::afficher () const
{
    Vehicule::afficher();
    cout << "tirant d'eau = " << tirant << endl;
}

class Amphibie : public Terrestre, public Marin
{
public :
    Amphibie (int nserieTer, int nserieMar, int nbr, int tir);
    void afficher () const;

private :
};

Amphibie::Amphibie (int nserTer, int nserMar, int nbr, int tir)
    : Terrestre(nserTer,nbr), Marin(nserMar,tir)
{
}

void Amphibie::afficher () const
{
    Terrestre::afficher();
    Marin::afficher();
}

int main ()
{
    Terrestre terre1 (1000, 4);
    Marin mer1 (2000, 8);
    Amphibie amphi1 (1111, 2222, 10, 5);

    terre1.afficher();
    mer1.afficher();
    amphi1.afficher();

    return 0;
}
