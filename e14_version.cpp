// e14.cpp

#include <iostream>
#include <cstring>
using namespace std;

/* la classe Animal ne peut definir le contenu de la fonction parler(),
 * celle-ci est donc declaree virtuelle pure et la classe est abstraite;
 */
class Animal
{
public :
    Animal (const char* no, const char* ca)
    {
        strcpy (nom, no);
        strcpy (carac, ca);
    }

    void afficher () const    { cout << nom << ", " << carac << endl; }
    virtual void parler () const = 0;

private :
    char nom[50];
    char carac[50];
};

/* la caracteristique etant la meme pour tous les chiens, elle n'a pas besoin
 * d'etre passee au constructeur de Chien;
 * idem pour les autres classes
 */
class Chien : public Animal
{
public :
    Chien (const char* no)
        : Animal(no,"reste fidele")
    { }

    void parler () const    { cout << "aboie" << endl; }

private :
};

class Cheval : public Animal
{
public :
    Cheval (const char* no)
        : Animal(no,"galope")
    { }

    void parler () const    { cout << "hennit" << endl; }

private :
};

class Oiseau : public Animal
{
public :
    Oiseau (const char* no)
        : Animal(no,"vole")
    { }

    // la classe Oiseau ne peut pas definir le contenu de parler()
	// => classe abstraite

private :
};

class Pigeon : public Oiseau
{
public :
    Pigeon (const char* no)
        : Oiseau(no)
    { }

    void parler () const    { cout << "roucoule" << endl; }

private :
};

class Corbeau : public Oiseau
{
public :
    Corbeau (const char* no)
        : Oiseau(no)
    { }

    void parler () const    { cout << "croasse" << endl; }

private :
};

class Rossignol : public Oiseau
{
public :
    Rossignol (const char* no)
        : Oiseau(no)
    { }

    void parler () const    { cout << "chante" << endl; }

private :
};

const int TAILLE = 100;

class ListeAnimaux
{
public :
    ListeAnimaux ();
    void ajouter (Animal& ani);    // passage par reference car dans l'enonce
                                   // on passe les variables, pas leurs adresses
    void afficher () const;

private :
    Animal* animaux[TAILLE];  // tableau de pointeurs
    int nb;                   // nombre d'elements ajoutes au tableau
};

ListeAnimaux::ListeAnimaux ()
{
    nb = 0;
}

void ListeAnimaux::ajouter (Animal& ani)
{
    if (nb < TAILLE)
    {
        animaux[nb] = &ani;
        nb++;
    }
}

void ListeAnimaux::afficher () const
{
    for (int i = 0; i < nb; i++)
    {
        cout << "**********" << endl;
        animaux[i]->afficher();
        animaux[i]->parler();
    }
}

int main ()
{
    Chien monChien ("Medor");
    Cheval monCheval ("Crin blanc");
    Pigeon monPigeon ("Petit Pigeon");
    Corbeau monCorbeau ("Petit Corbeau");
    Rossignol monRossignol ("Petit Rossignol");

    ListeAnimaux liste;

    liste.ajouter (monChien);
    liste.ajouter (monCheval);
    liste.ajouter (monPigeon);
    liste.ajouter (monCorbeau);
    liste.ajouter (monRossignol);

    liste.afficher();

    return 0;
}
