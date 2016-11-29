// e19.cpp

#include <iostream>
#include <string>
using namespace std;
#include "str1.h"

const int TAILLE = 100;

template <class T>
class Ensemble
{
public :
    Ensemble ();
    void ajouter (T val);
    bool contient (T val) const;
    void afficher () const;

private :
    T elem[TAILLE];
    int nb;
};

template <class T>
Ensemble<T>::Ensemble ()
{
    nb = 0;
}

template <class T>
void Ensemble<T>::ajouter (T val)
{
    if (nb < TAILLE && !contient(val))
    {
        elem[nb] = val;
        nb++;
    }
}

template <class T>
bool Ensemble<T>::contient (T val) const
{
    int i = 0;

    while (val != elem[i] && i < nb)
        i++;

    if (i < nb)
        return true;
    else
        return false;
}

template <class T>
void Ensemble<T>::afficher () const
{
    for (int i = 0; i < nb; i++)
        cout << elem[i] << " ";

    cout << endl;
}

int main ()
{
    Ensemble<int> ens1;
    ens1.ajouter (10);
    ens1.ajouter (5);
    ens1.ajouter (10);
    ens1.ajouter (15);
    ens1.afficher();

    Ensemble<string> ens2;
    string s1 ("bonjour");
    ens2.ajouter (s1);
    ens2.ajouter ("salut");
    ens2.ajouter ("bonjour");
    ens2.ajouter ("toto");
    ens2.afficher();

    Ensemble<String> ens3;
    String st1 ("bonjour");
    ens3.ajouter (st1);
    ens3.ajouter ("salut");
    ens3.ajouter ("bonjour");
    ens3.ajouter ("toto");
    ens3.afficher();

    /* dans le cas de ens3 on passe a la fonction ajouter des char*, alors
	 * qu'elle attend un objet String : on utilise la conversion * automatique
	 * d'un char* en objet String due au constructeur String(const char*);
	 * idem pour ens2 et la classe string
     */

    return 0;
}
