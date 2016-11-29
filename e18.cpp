// e18.cpp

#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

// classe de l'exception de debordement
class Deborde
{
public :
    Deborde (long v, const char* m)     { val = v; strcpy (msg, m); }
    long getVal () const                { return val; }
    void afficherMsg () const           { cout << msg << endl; }

private :
    long val;       // valeur ayant entraine le debordement
    char msg[100];  // message d'erreur
};

class SHORT
{
public :
    SHORT (long v);
    friend ostream& operator<< (ostream& flot, const SHORT& s);
    SHORT operator+ (const SHORT& s2) const;
    SHORT operator- (const SHORT& s2) const;
    SHORT operator* (const SHORT& s2) const;
    SHORT operator/ (const SHORT& s2) const;

private :
    short val;
};

SHORT::SHORT (long v)
{
    if (v > SHRT_MAX)
    {
        Deborde deb (v, "debordement par le haut");
        throw deb;
    }
    else if (v < SHRT_MIN)
    {
        Deborde deb (v, "debordement par le bas");
        throw deb;
    }
    else
        val = (short)v;
}

/* les operateurs n'ont pas besoin de tester explicitement le debordement : ils
 * font les calculs sur des "long" et retournent un objet SHORT resultat => le
 * constructeur de cet objet teste le debordement
 */

SHORT SHORT::operator+ (const SHORT& s2) const
{
    long v = val, v2 = s2.val;
    SHORT resultat (v + v2);
    return resultat;
}

SHORT SHORT::operator- (const SHORT& s2) const
{
    long v = val, v2 = s2.val;
    SHORT resultat (v - v2);
    return resultat;
}

SHORT SHORT::operator* (const SHORT& s2) const
{
    long v = val, v2 = s2.val;
    SHORT resultat (v * v2);
    return resultat;
}

SHORT SHORT::operator/ (const SHORT& s2) const
{
    long v = val, v2 = s2.val;
    SHORT resultat (v / v2);
    return resultat;
}

ostream& operator<< (ostream& flot, const SHORT& s)
{
    flot << s.val;
    return flot;
}

int main ()
{
    long x, y;
    cout << "saisir deux valeurs : ";
    cin >> x >> y;

    try
    {
        cout << "debut du bloc try" << endl;
        SHORT s1(x), s2(y);

        cout << "somme = "     << s1 + s2 << endl;
        cout << "diff = "      << s1 - s2 << endl;
        cout << "produit = "   << s1 * s2 << endl;
        cout << "quotient = "  << s1 / s2 << endl;
        cout << "suite du bloc try" << endl;
    }
    catch (Deborde excep)
    {
        cout << endl;
        excep.afficherMsg();
        cout << excep.getVal() << endl;
    }
    cout << "suite du main" << endl;

    return 0;
}
