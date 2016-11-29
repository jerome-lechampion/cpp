// e15_2.cpp
// exercice E15 2eme partie

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

 /* pour que Amphibie affiche une seule fois ses donnees de Vehicule, Terrestre
  * et Marin offre en partie protegee (donc accessible uniquement a leurs
  * classes filles) une fonction d'affichage de leurs donnees specifiques
  */

class Terrestre : public virtual Vehicule
{
public :
    Terrestre (int nserie, int nbr);
    void afficher () const;

    void f () {}    // on definit f sinon la classe serait abstraite

protected  :
    void afficherSpec () const;

private :
    int nbRoues;
};

Terrestre::Terrestre (int nserie, int nbr)
    : Vehicule (nserie)
{
    nbRoues = nbr;
}

// affichage de toutes les donnees d'un objet Terrestre
void Terrestre::afficher () const
{
    Vehicule::afficher();
    afficherSpec();
}

// affichage des donnees specifiques de la classe Terrestre
void Terrestre::afficherSpec () const
{
    cout << nbRoues << " roues" << endl;
}

class Marin : public virtual Vehicule
{
public :
    Marin (int nserie, int tir);
    void afficher () const;

    void f () {}    // on definit f sinon la classe serait abstraite

protected  :
    void afficherSpec () const;

private :
    int tirant;
};

Marin::Marin (int nserie, int tir)
    : Vehicule (nserie)
{
    tirant = tir;
}

// affichage de toutes les donnees d'un objet Marin
void Marin::afficher () const
{
    Vehicule::afficher();
    afficherSpec();
}

// affichage des donnees specifiques de la classe Marin
void Marin::afficherSpec () const
{
    cout << "tirant d'eau = " << tirant << endl;
}

class Amphibie : public Terrestre, public Marin
{
public :
    Amphibie (int nserie, int nbr, int tir);

    // 1ere version avec les deux numeros de serie terrestre et marin :
    // Amphibie (int nserieTer, int nserieMar, int nserie, int nbr, int tir);

    void afficher () const;

    // on definit f sinon le compilateur indique un conflit entre les 2
    // fonctions f heritees de Terrestre et Marin
    void f () {}

private :
};

/* Amphibie derivant une seule fois de Vehicule elle doit appeler explicitement
 * le constructeur de Vehicule meme si celle-ci n'est pas une classe mere
 * directe
 */
Amphibie::Amphibie (int nserie, int nbr, int tir)
    : Vehicule(nserie), Terrestre(nserie,nbr), Marin(nserie,tir)
{
}
/* 1ere version avec les deux numeros de serie terrestre et marin :
Amphibie::Amphibie (int nserTer, int nserMar, int nserie, int nbr, int tir)
    : Vehicule(nserie), Terrestre(nserTer,nbr), Marin(nserMar,tir)
{
}
*/

void Amphibie::afficher () const
{
    /* si on appelait Tesrrestre::afficher et Marin::afficher on afficherait
     * deux fois les donnees communes heritees de Vehicule
     */
    Vehicule::afficher();
    Terrestre::afficherSpec();
    Marin::afficherSpec();
}

int main ()
{
    Terrestre terre1 (1234, 4);
    Marin mer1 (1000, 8);
    Amphibie amphi1 (3333, 10, 5);

    terre1.afficher();
    mer1.afficher();
    amphi1.afficher();

    return 0;
}
