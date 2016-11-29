// employe.cpp

#include <iostream>
#include <cstring>
using namespace std;

class Employe
{
public :
    Employe (const char* no, int sal);
    void afficheNom () const;
    int calculPaie () const;

private :
    char nom [20];
    int salaire;
};

Employe::Employe (const char* no, int sal)
{
    strcpy (nom, no);
    salaire = sal;
}

void Employe::afficheNom () const
{
    cout << "nom : " << nom << endl;
}

int Employe::calculPaie () const
{
    // retourne le salaire fixe
}

class Ouvrier : public Employe
{
public :
    Ouvrier (const char* no, int sal, int tx);
    void ajoutHeures (int nbH);
    int calculPaie () const;

private :
    int taux;
    int nbHeures;
};

Ouvrier::Ouvrier (const char* no, int sal, int tx)
    : Employe (no,sal)
{
    taux = tx;
    nbHeures = 0;
}

void Ouvrier::ajoutHeures (int nbH)
{
    nbHeures += nbH;
}

int Ouvrier::calculPaie () const
{
    // salaire fixe + heures sup
}

class Cadre : public Employe
{
public :
    Cadre (const char* no, int sal, int pri);
    int calculPaie () const;

private :
    int prime;
};

Cadre::Cadre (const char* no, int sal, int pri)
    : Employe (no,sal)
{
    prime = pri;
}

int Cadre::calculPaie () const
{
    // salaire fixe + prime
}

class Liste
{
public :
    Liste ();
    void ajouter (Employe* pEmpl);
    void afficherPaies () const;

private :
    Employe* tab[100];
    int nb;
};

Liste::Liste ()
{
    // a ecrire
}

void Liste::ajouter (Employe* pEmpl)
{
    // a ecrire
}

void Liste::afficherPaies () const
{
    // a ecrire
}

int main ()
{
    return 0;
}
