// employe_1.cpp
//
//  exercice sur les employes, partie I fonctions virtuelles

#include <iostream>
#include <cstring>
using namespace std;

class Employe
{
public :
    Employe (const char* no, int sal);
    void afficheNom () const;
    //int calculPaie () const;
    virtual int calculPaie () const;

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
    return salaire;
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
    return Employe::calculPaie() + taux * nbHeures;
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
    return Employe::calculPaie() + prime;
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
    nb = 0;
}

void Liste::ajouter (Employe* pEmpl)
{
    if (nb < 100)
    {
        tab[nb] = pEmpl;
        nb++;
    }
}

void Liste::afficherPaies () const
{
    cout << "**********" << endl;

    for (int i = 0; i < nb; i++)
    {
        tab[i]->afficheNom();
        cout << tab[i]->calculPaie() << endl;
    }
}

int main ()
{
    Employe emp ("emp", 1500);
    Ouvrier ouv ("ouv", 1200, 15);
    Cadre cad ("cad", 3000, 500);
    ouv.ajoutHeures (10);

    emp.afficheNom();
    cout << emp.calculPaie() << endl;

    ouv.afficheNom();
    cout << ouv.calculPaie() << endl;

    cad.afficheNom();
    cout << cad.calculPaie() << endl;

    Liste lis;
    lis.ajouter (&emp);
    lis.ajouter (&ouv);
    lis.ajouter (&cad);

    lis.afficherPaies();

    return 0;
}
