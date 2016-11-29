// e12.cpp

#include <iostream>
#include <cstdlib>
using namespace std;

class Ratio
{
public :
    Ratio (int nu, int de = 1);

    void affecte (int nu, int de);

    friend ostream& operator<<  (ostream& flot, const Ratio& ra);

    Ratio operator+ (const Ratio& ra2) const;
    Ratio operator- (const Ratio& ra2) const;
    Ratio operator* (const Ratio& ra2) const;
    Ratio operator/ (const Ratio& ra2) const;

    Ratio& operator+= (const Ratio& ra2);
    Ratio& operator-= (const Ratio& ra2);
    Ratio& operator*= (const Ratio& ra2);
    Ratio& operator/= (const Ratio& ra2);

    bool operator== (const Ratio& ra2) const;
    bool operator!= (const Ratio& ra2) const;

    operator float () const;

private :
    int nume;    // numerateur
    int deno;    // denominateur

    void reduire ();    // reduit la fraction nume/deno

    /* retourne le pgcd de x et y;
     * fonction statique car n'a pas besoin d'un objet Ratio pour etre appelee
     */
    static int pgcd (int x, int y);
};

Ratio::Ratio (int nu, int de)
{
    // on se protege d'un denominateur nul
    if (de == 0)
    {
        cout << "denominateur nul" << endl;
        exit (0);
    }

    nume = nu;
    deno = de;
    reduire(); 
}

void Ratio::affecte (int nu, int de)
{
    nume = nu;
    deno = de;
    reduire();
}

ostream& operator<<  (ostream& flot, const Ratio& ra)
{
    /* on met le signe sur le numerateur et on n'affiche pas un denominateur
     * valant 1
     */

    int numeAffiche, denoAffiche;

    if (ra.deno < 0)
    {
        numeAffiche = -ra.nume;
        denoAffiche = -ra.deno;
    }
    else
    {
        numeAffiche = ra.nume;
        denoAffiche = ra.deno;
    }

    flot << numeAffiche;
    if (denoAffiche != 1)
        flot << "/" << denoAffiche;

    return flot;
}

Ratio Ratio::operator+ (const Ratio& ra2) const
{
    int numeResult = nume * ra2.deno + ra2.nume * deno;
    int denoResult = deno * ra2.deno;
    Ratio result (numeResult, denoResult);  // le constructeur reduit result
    return result;
}

Ratio Ratio::operator- (const Ratio& ra2) const
{
    int numeResult = nume * ra2.deno - ra2.nume * deno;
    int denoResult = deno * ra2.deno;
    Ratio result (numeResult, denoResult);
    return result;
}

Ratio Ratio::operator* (const Ratio& ra2) const
{
    int numeResult = nume * ra2.nume;
    int denoResult = deno * ra2.deno;
    Ratio result (numeResult, denoResult);
    return result;
}

Ratio Ratio::operator/ (const Ratio& ra2) const
{
    int numeResult = nume * ra2.deno;
    int denoResult = deno * ra2.nume;
    Ratio result (numeResult, denoResult);
    return result;
}

// dans +=, -=, *=, /= on appelle les operateurs +, -, *, / precedents

Ratio& Ratio::operator+= (const Ratio& ra2)
{
    *this = *this + ra2;
    return *this;
}

Ratio& Ratio::operator-= (const Ratio& ra2)
{
    *this = *this - ra2;
    return *this;
}

Ratio& Ratio::operator*= (const Ratio& ra2)
{
    *this = *this * ra2;
    return *this;
}

Ratio& Ratio::operator/= (const Ratio& ra2)
{
    *this = *this / ra2;
    return *this;
}

bool Ratio::operator== (const Ratio& ra2) const
{
    return nume * ra2.deno == ra2.nume * deno;
}

bool Ratio::operator!= (const Ratio& ra2) const
{
    // on appelle l'operateur == precedent
    return !(*this == ra2);
}

Ratio::operator float () const
{
    // on force la division entre flottants
    return (float)nume / (float)deno;
}

void Ratio::reduire ()
{
    int lePgcd = pgcd (nume, deno);
    nume = nume / lePgcd;
    deno = deno / lePgcd;
}

// on utilise l'algorithme recursif : pgcd (x,y) = pgcd (y,reste de x/y)
int Ratio::pgcd (int x, int y)
{
    int valPgcd;

    if (x % y == 0)
        valPgcd = y;
    else
        valPgcd = pgcd (y, x % y);

    return valPgcd;
}

int main ()
{
    Ratio r1(18,-4), r2(9);

    cout << r1 << " , " << r2 << endl;

    Ratio r3(3,5), r4(5), r5(-4,3), r6(2,3);

    cout << r1 + r3 << endl;
    cout << r1 - r4 << endl;
    cout << r1 * r5 << endl;
    cout << r1 / r6 << endl;

    r2 += r3;
    r2 -= r4;
    r2 *= r5;
    r2 /= r6;
    cout << r2 << endl;

    Ratio r7(-46,5);
    if (r2 == r7 && r2 != r1)
        cout << "operateurs == et != ok" << endl;

    r1.affecte (-3,2);
    r2.affecte (6,21);
    cout << r1 << " = " << (float)r1 << endl;
    cout << r2 << " = " << (float)r2 << endl;

    Ratio r8(5,0);    // test erreur denominateur nul
    cout << r8 << endl;

    return 0;
}
