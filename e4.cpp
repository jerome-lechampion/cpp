// e4.cpp

#include <iostream>
using namespace std;

const int TAILLE = 100;    // nb max d'elements dans un ensemble

class Ensemble
{
public :
    Ensemble ();
    void ajouter (int x);
    void retirer (int x);
    bool contient (int x) const;
    bool estEgal (const Ensemble& ens2) const;
    void afficher () const;

private :
    int elem [TAILLE];    // elements de l'ensemble
    int nbElem;           // nb d'elements presents dans l'ensemble

    int chercher (int x) const; // cherche x dans l'ensemble, retourne son
                                // indice dans elem ou -1 si non trouve
};

Ensemble::Ensemble ()
{
    nbElem = 0;
}

void Ensemble::ajouter (int x)
{
    // on verifie qu'il y a de la place dans l'ensemble
    if (nbElem < TAILLE)
    {
        // x est ajoute seulement s'il n'est pas deja dans l'ensemble
        if (!contient(x))
        {
            elem [nbElem] = x;
            nbElem++;
        }
    }
}

void Ensemble::retirer (int x)
{
    int indice_x;

    indice_x = chercher (x);

    // si x a ete trouve dans l'ensemble
    if (indice_x >= 0)
    {
        // pour retirer x on peut decaler les elements suivants ou le remplacer
        // par le dernier element (solution retenue)
        elem [indice_x] = elem [nbElem - 1];
        nbElem--;
    }
}

bool Ensemble::contient (int x) const
{
    bool contenance;

    if (chercher(x) >= 0)
        contenance = true;
    else
        contenance = false;

    return contenance;
}

bool Ensemble::estEgal (const Ensemble& ens2) const
{
    // les ensembles sont egaux s'ils ont meme nb d'elements et si l'un des 2
    // contient chaque element de l'autre

    bool egaux;

    if (nbElem != ens2.nbElem)
        egaux = false;
    else
    {
        // test pour savoir si ens2 contient chaque element de l'ensemble
        // courant

        int i = 0;
        while (i < nbElem && ens2.contient(elem[i]))
            i++;

        if (i < nbElem)
            egaux = false;
        else
            egaux = true;
    }

    return egaux;
}

void Ensemble::afficher () const
{
    cout << "( ";

    for (int i = 0; i < nbElem; i++)
        cout << " " << elem[i];
    
    cout << " )" << endl;
}

int Ensemble::chercher (int x) const
{
    int indice;

    int i = 0;
    while (i < nbElem && x != elem[i])
        i++;

    if (i < nbElem)
        indice = i;
    else
        indice = -1;

    return indice;
}

int main ()
{
    Ensemble e1;

    e1.ajouter (2);
    e1.ajouter (8);
    e1.ajouter (6);
    e1.ajouter (5);
    e1.ajouter (2);
    e1.afficher ();

    e1.retirer (8);
    e1.retirer (5);
    e1.afficher ();

    Ensemble e2, e3;
    e2.ajouter (2);
    e2.ajouter (6);
    e3.ajouter (6);
    e3.ajouter (2);

    if (e1.contient(6) || !e1.contient(5))
        cout << "contient ok" << endl;

    e3.ajouter (7);

    if (e1.estEgal(e2) && !e1.estEgal(e3))
        cout << "estEgal ok" << endl;

    return 0;
}

