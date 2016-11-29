// e7.cpp

#include <iostream>
using namespace std;

// les donnees comportant un pointeur sur un tableau alloue specifiquement
// pour chaque objet, il est necessaire d'ecrire un constructeur par copie et
// un destructeur

class Ensemble
{
public :
    Ensemble (int laTaille);          // constructeur ensemble vide
    Ensemble (const Ensemble& ens2);  // constructeur par copie
    ~Ensemble ();
    void ajouter (int x);
    void retirer (int x);
    bool contient (int x) const;
    bool estEgal (const Ensemble& ens2) const;
    void afficher () const;

private :
    int* elem;      // elements de l'ensemble : tableau alloue dynamiquement
                    // en fonction de la taille passee au constructeur
    int taille;     // taille du tableau d'elements : nb max. d'elements
    int nbElem;     // nb d'elements presents dans l'ensemble (compris entre
                    // 0 et taille)

    int chercher (int x) const;  // cherche x dans l'ensemble, retourne son
                                 // indice dans elem ou -1 si non trouve
};

Ensemble::Ensemble (int laTaille)
{
    elem = new int [laTaille];
    taille = laTaille;
    nbElem = 0;
}

Ensemble::Ensemble (const Ensemble& ens2)
{
    // allocation d'un tableau a la meme taille que celui de ens2 et copie des
    // elements de ens2

    elem = new int [ens2.taille];
    taille = ens2.taille;

    for (int i = 0; i < ens2.nbElem; i++)
        elem[i] = ens2.elem[i];
    nbElem = ens2.nbElem;
}

Ensemble::~Ensemble ()
{
    delete [] elem;
}

void Ensemble::ajouter (int x)
{
    // on verifie qu'il y a de la place dans l'ensemble
    if (nbElem < taille)
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
    int indice;

    indice = chercher (x);

    // si x a ete trouve dans l'ensemble
    if (indice >= 0)
    {
        // pour retirer x on peut decaler les elements suivants ou le remplacer
        // par le dernier element (solution retenue)
        elem [indice] = elem [nbElem - 1];
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
    Ensemble e1(4);

    e1.ajouter (2);
    e1.ajouter (8);
    e1.ajouter (6);
    e1.ajouter (5);
    e1.ajouter (2);
    e1.ajouter (10);    // taille (4) deja atteinte
    e1.afficher ();

    e1.retirer (8);
    e1.retirer (5);
    e1.afficher ();

    Ensemble e2(50);
    e2.ajouter (2);
    e2.ajouter (6);
    Ensemble e3 = e2;

    if (e1.contient(6) || !e1.contient(5))
        cout << "appartient ok" << endl;

    e3.ajouter (7);

    if (e1.estEgal(e2) && !e1.estEgal(e3))
        cout << "estEgal ok" << endl;

    return 0;
}

