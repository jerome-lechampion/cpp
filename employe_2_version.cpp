// employe_2.cpp
//
// exercice sur les employes, partie II fonctions virtuelles pures

#include <iostream>
#include <cstring>
using namespace std;

class Employe
{
public :
    Employe (const char* no);
    void afficheNom () const;
    virtual int calculPaie () const = 0;

private :
    char nom [20];
};

Employe::Employe (const char* no)
{
    strcpy (nom, no);
}

void Employe::afficheNom () const
{
    cout << "nom : " << nom << endl;
}

class Ouvrier : public Employe
{
public :
    Ouvrier (const char* no, int tx);
    void ajoutHeures (int nbH);
    int calculPaie () const;

private :
    int taux;
    int nbHeures;
};

Ouvrier::Ouvrier (const char* no, int tx)
    : Employe (no)
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
    return taux * nbHeures;
}

class Cadre : public Employe
{
public :
    Cadre (const char* no, int pri);
    int calculPaie () const;

private :
    int prime;
};

Cadre::Cadre (const char* no, int pri)
    : Employe (no)
{
    prime = pri;
}

int Cadre::calculPaie () const
{
    return prime;
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
    //Employe emp ("emp");
    Ouvrier ouv ("ouv", 15);
    Cadre cad ("cad", 4000);
    ouv.ajoutHeures (100);

    /*emp.afficheNom();
    cout << emp.calculPaie() << endl;*/

    ouv.afficheNom();
    cout << ouv.calculPaie() << endl;

    cad.afficheNom();
    cout << cad.calculPaie() << endl;

    Liste lis;
    //lis.ajouter (&emp);
    lis.ajouter (&ouv);
    lis.ajouter (&cad);

    lis.afficherPaies();

    return 0;
}
