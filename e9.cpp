// e9.cpp

#include <iostream>
using namespace std;
#include "str.h"

// il y a un seul taux et une seule tete de liste pour tous les Compte, ces
// donnees sont donc statiques

// de meme, les fonctions de la classe qui ne s'appliquent pas sur un objet
// Compte sont statiques : c'est le cas des fonctions qui agissent sur le taux
// ou qui parcourent la liste

class Compte
{
public :
    Compte (const char* no, float montantIni = 0);
    ~Compte ();
    void verser (float montantVerse);
    void actualiser ();
    void afficher () const;
    static void modifierTaux (float nouveauTaux);
    static void actualiserTous ();
    static void afficherTous ();

private :
    String nom;
    float montant;
    Compte* suiv;    // pour le dernier compte du chainage : suiv = 0

    static float taux;    // valeur exprimee en pourcentage
    static Compte* tete;
};

float Compte::taux = 3.5;   // taux initial
Compte*  Compte::tete = 0;  // liste vide initialement;
                            // remarque : en C++ on peut utiliser 0 pour NULL

/* dans la liste d'initialisation, appel du constructeur de l'objet membre nom
 */
Compte::Compte (const char* no, float montantIni)
    : nom(no)
{
    montant = montantIni;

    /* insertion du compte, c'est a dire de l'objet courant, en debut de
     * liste
     */
    suiv = tete;    // le compte est chaine sur l'ancienne tete
    tete = this;    // il devient la nouvelle tete
}

// le destructeur supprime le compte de la liste
Compte::~Compte ()
{
    Compte* prec = 0;
    Compte* compte = tete;

    /* parcours de la liste a la recherche du compte, tout en gardant trace de
     * son precedent
     */
    while (compte != this) // la recherche est faite en comparant les adresses
    {
        prec = compte; 
        compte = compte->suiv;
    }

    // on sort necessairement de la boucle en ayant trouve le compte

    /* on supprime le compte de la liste en chainant son precedent sur son
     * suivant, ou en chainant la tete de liste sur son suivant s'il n'a pas de
     * precedent
     */
    if (prec != 0)
        prec->suiv = compte->suiv;
    else
        tete = compte->suiv;
}

void Compte::verser (float montantVerse)
{
    montant += montantVerse;
}

void Compte::actualiser ()
{
    montant *= (1 + taux / 100);
}

void Compte::afficher () const
{
    nom.afficher();
    cout << "montant : " << montant << endl;
}

void Compte::modifierTaux (float nouveauTaux)
{
    taux = nouveauTaux;
}

void Compte::actualiserTous ()
{
    // parcours du chainage pour actualiser chacun des comptes
    Compte* compte = tete;
    while (compte != 0)
    {
        compte->actualiser();
        compte = compte->suiv;
    }
}

void Compte::afficherTous ()
{
    // parcours du chainage pour afficher chacun des comptes
    Compte* compte = tete;
    while (compte != 0)
    {
        compte->afficher();
        compte = compte->suiv;
    }
}

int main ()
{
    /*** test partie I ***/

    /* certains comptes sont crees par new pour pouvoir les supprimer par
     * delete
     */
    Compte* cpt1 = new Compte ("xy1", 1200);
    Compte cpt2 ("xy2");
    Compte* cpt3 = new Compte ("xy3", 600);
    Compte cpt4 ("xy4");
    Compte* cpt5 = new Compte ("xy5");

    cpt1->verser (100);
    cpt2.verser (200);
    cpt3->verser (50);
    cpt4.verser (10);
    cpt5->verser (20);

    cpt1->actualiser();
    cpt2.actualiser();
    cpt3->actualiser();
    cpt4.actualiser();
    cpt5->actualiser();

    cpt1->afficher();
    cpt2.afficher();
    cpt3->afficher();
    cpt4.afficher();
    cpt5->afficher();

    cout << endl << "taux a 2%" << endl;
    Compte::modifierTaux (2.0);

    cpt1->actualiser();
    cpt2.actualiser();
    cpt3->actualiser();
    cpt4.actualiser();
    cpt5->actualiser();

    cpt1->afficher();
    cpt2.afficher();
    cpt3->afficher();
    cpt4.afficher();
    cpt5->afficher();


    /*** test partie II ***/

    cout << endl << "affichage par la liste :" << endl;
    Compte::afficherTous();

    // on detruit des comptes => ils sont retires du chainage
    cout << endl << "on retire 5, 1, 3" << endl;
    delete cpt5;
    delete cpt1;
    delete cpt3;

    cout << endl << "taux a 5%" << endl;
    Compte::modifierTaux (5.0);

    Compte::actualiserTous();
    Compte::afficherTous();

    return 0;
}

