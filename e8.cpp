// e8.cpp

#include <iostream>
using namespace std;

class Complexe
{
public :
    Complexe (float r, float i);
    Complexe (float r);

    void afficher () const;
    void ajouter (const Complexe& cx2);

    Complexe add (const Complexe& cx2) const;
    friend Complexe add (const Complexe& cx1, const Complexe& cx2);

private :
    float re, im;
};

Complexe::Complexe (float r, float i)
{
    re = r;
    im = i;
}

Complexe::Complexe (float r)
{
    re = r;
    im = 0;
}

void Complexe::afficher () const
{
    cout << re << " + " << im << "i" << endl;
}

void Complexe::ajouter (const Complexe& cx2)
{
    re += cx2.re;
    im += cx2.im;
}

Complexe Complexe::add (const Complexe& cx2) const
{
    Complexe result (re + cx2.re, im + cx2.im);
    return result;
}

Complexe add (const Complexe& cx1, const Complexe& cx2)
{
    Complexe result (cx1.re + cx2.re, cx1.im + cx2.im);
    return result;
}

int main ()
{
    float a, b;
    cout << "saisir un complexe : ";
    cin >> a >> b;

    Complexe c1 (a,b);
    Complexe c2 (3.1);
    Complexe c3 (2,5);

    c1.ajouter (c2);
    c1.ajouter (c3);
    cout << "apres ajout de 3.1 et 2+5i : ";
    c1.afficher();

    Complexe c4 (5,6), c5 (2,9);
    Complexe c6 = c4.add (c5);
    Complexe c7 = add (c4, c5);
    cout << "deux additions de 5+6i et 2+9i : " << endl;
    c6.afficher();
    c7.afficher();

    return 0;
}

