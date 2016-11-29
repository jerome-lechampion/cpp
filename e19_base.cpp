// e19.cpp

#include <iostream>
using namespace std;

const int TAILLE = 100;

class Ensemble
{
public :
    Ensemble ();
    void ajouter (int val);
    bool contient (int val) const;
    void afficher () const;

private :
    int elem[TAILLE];
    int nb;
};

Ensemble::Ensemble ()
{
    nb = 0;
}

void Ensemble::ajouter (int val)
{
    if (nb < TAILLE && !contient(val))
    {
        elem[nb] = val;
        nb++;
    }
}

bool Ensemble::contient (int val) const
{
    int i = 0;

    while (val != elem[i] && i < nb)
        i++;

    if (i < nb)
        return true;
    else
        return false;
}

void Ensemble::afficher () const
{
    for (int i = 0; i < nb; i++)
        cout << elem[i] << " ";

    cout << endl;
}

int main ()
{
    return 0;
}
