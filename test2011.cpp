// test2011.cpp

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <iomanip>
using namespace std;

const int MAXCAR = 100;

class Chaine
{
public :
    Chaine()                    { str[0] = '\0'; }
    Chaine (const char* str2)   { strcpy(str, str2); }
    friend ostream& operator<< (ostream& flot, const Chaine& cha);
    friend istream& operator>> (istream& flot, Chaine& cha);
    int length() const;
    char charAt (int i) const;
    void setCharAt (int i, char newChar);
    void copyTo (char* dest) const;
    void copyFrom (const char* source);
    bool equals (const Chaine& chaine2) const;
    Chaine toLowerCase() const;

private :
    char str [MAXCAR + 1];
};

ostream& operator<< (ostream& flot, const Chaine& cha)
{
    flot << cha.str;
    return flot;
}

istream& operator>> (istream& flot, Chaine& cha)
{
    flot >> cha.str;
    return flot;
}

int Chaine::length() const
{
    return strlen(str);
}

char Chaine::charAt (int i) const
{
    return str[i];
}

void Chaine::setCharAt (int i, char newChar)
{
    str[i] = newChar;
}

void Chaine::copyTo (char* dest) const
{
    strcpy (dest, str);
}

void Chaine::copyFrom (const char* source)
{
    strcpy (str, source);
}

bool Chaine::equals (const Chaine& chaine2) const
{
    return strcmp(str, chaine2.str) == 0;
}

Chaine Chaine::toLowerCase() const
{
    Chaine chaineMin;

    int lg = strlen(str);

    for (int i = 0; i < lg; i++)
        chaineMin.str[i] = tolower(str[i]);

    chaineMin.str[lg] = '\0';

    return chaineMin;
}

class ChaineNoCasse : public Chaine
{
public :
    ChaineNoCasse();
    ChaineNoCasse (const char* str2);
    bool operator== (const ChaineNoCasse& chaine2) const;
};

ChaineNoCasse::ChaineNoCasse()
    : Chaine()
{
}

ChaineNoCasse::ChaineNoCasse (const char* str2)
    : Chaine(str2)
{
}

bool ChaineNoCasse::operator== (const ChaineNoCasse& chaine2) const
{
    Chaine chaineMin = toLowerCase();
    Chaine chaineMin2 = chaine2.toLowerCase();
    return chaineMin.equals(chaineMin2);
}

class Date
{
public :
    Date();
    Date (int j, int m, int a);
    int getJour() const     { return jour; }
    int getMois() const     { return mois; }
    int getAnnee() const    { return annee; }
    void setJour(int j)     { jour = j; }
    void setMois(int m)     { mois = m; }
    void setAnnee(int a)    { annee = a; }
    friend ostream& operator<< (ostream& flot, const Date& da);

private :
    int jour, mois, annee;
};

Date::Date()
{
    jour = 1;
    mois = 1;
    annee = 2000;
}

Date::Date (int j, int m, int a)
{
    jour = j;
    mois = m;
    annee = a;
}

ostream& operator<< (ostream& flot, const Date& da)
{
    flot << setfill('0') << setw(2) << da.jour << "/" << setw(2) << da.mois
            << "/" << da.annee;
    return flot;
}

class Individu
{
public :
    Individu();
    Individu (const char* leNom, int jourNaiss, int moisNaiss, int anneeNaiss);
    void setIndividu (const char* leNom, int jourNaiss, int moisNaiss,
                                                            int anneeNaiss);
    void afficher (bool miseEnForme = false) const;

private :
    Chaine nom;
    Date dateNaissance;
};

Individu::Individu()
    : nom("anonyme"), dateNaissance(0,0,0)
{
}

Individu::Individu (const char* leNom, int jourNaiss, int moisNaiss,
                                                        int anneeNaiss)
    : nom(leNom), dateNaissance(jourNaiss,moisNaiss,anneeNaiss)
{
}

void Individu::setIndividu (const char* leNom, int jourNaiss, int moisNaiss,
                                                                int anneeNaiss)
{
    nom.copyFrom (leNom);
    dateNaissance.setJour (jourNaiss);
    dateNaissance.setMois (moisNaiss);
    dateNaissance.setAnnee (anneeNaiss);
}

void Individu::afficher (bool miseEnForme) const
{
    if (miseEnForme)
    {
        Chaine nomFormate = nom.toLowerCase();
        char premierCar = nomFormate.charAt(0);
        nomFormate.setCharAt(0, toupper(premierCar));
        cout << nomFormate;
    }
    else
        cout << nom;

    cout  << " né le "  << dateNaissance << endl;
}

class ExceptionChaine
{
public :
    ExceptionChaine (const char* message)   { strcpy (msg, message); }
    void afficher() const                   { cout << msg << endl; }

private :
    char msg[100];
};

class ChaineEtendue : public Chaine
{
public :
    ChaineEtendue();
    ChaineEtendue (const char* str2);
    bool operator== (const ChaineEtendue& chaine2) const;
    ChaineEtendue operator+ (const ChaineEtendue& chaine2) const;
    int indexOf (char c) const;
    ChaineEtendue substring(int begin, int end) const;
};

ChaineEtendue::ChaineEtendue()
    : Chaine()
{
}

ChaineEtendue::ChaineEtendue (const char* str2)
    : Chaine(str2)
{
}

bool ChaineEtendue::operator== (const ChaineEtendue& chaine2) const
{
    return equals(chaine2);
}

ChaineEtendue ChaineEtendue::operator+ (const ChaineEtendue& chaine2) const
{
    if (length() + chaine2.length() > MAXCAR)
        throw ExceptionChaine ("débordement +");

    char strResult[MAXCAR+1], str2[MAXCAR+1];

    copyTo (strResult);
    chaine2.copyTo (str2);
    strcat (strResult, str2);    

    ChaineEtendue chaineResult (strResult);
    return chaineResult;
}

int ChaineEtendue::indexOf (char c) const
{
    int lg = length();
    int i = 0;
    while (charAt(i) != c && i < lg)
        i++;
    if (i < lg)
        return i;
    else
        return -1;
}

ChaineEtendue ChaineEtendue::substring(int begin, int end) const
{
    int lg = length();
    if (begin < 0 || end >= lg || begin > end)
        throw ExceptionChaine ("indices sous-chaine incorrects");
 
    char strResult[MAXCAR+1];

    for (int i = begin; i <= end; i++)
        strResult[i-begin] = charAt(i);

    strResult[end-begin + 1] = '\0';

    ChaineEtendue chaineResult(strResult);
    return chaineResult;
}

int main ()
{
    // TEST CHAINE
    /*
    Chaine ch1;
    cin >> ch1;
    cout << ch1 << endl;
    ch1.setCharAt(2, 'X');
    cout << "lg=" << ch1.length() << "," << ch1 << "," << ch1.charAt(3) << endl;
    char s1[MAXCAR+1], s2[50];
    ch1.copyTo(s1);
    strcpy(s2, "BONJOUR");
    ch1.copyFrom(s2);
    cout << s1 << "," << ch1 << endl;
    Chaine ch2 = ch1, ch3 = ch1;
    ch3.setCharAt(2, 'Y');
    if (ch1.equals(ch2) && !ch1.equals(ch3))
        cout << "equals ok" << endl;
    Chaine ch4 = ch1.toLowerCase();
    cout << ch4 << endl;
    */

    // TEST CHAINE NO CASSE
    /*
    ChaineNoCasse chn1("SaLut"), chn2("SAlut"), chn3("bonjour");
    if (chn1 == chn2 && !(chn1 == chn3))
        cout << "== ChaineNoCasse ok" << endl;
    */

    // TEST DATE ET INDIVIDU
    Date d0, d1(12,8,2011);
    cout << d0 << " " << d1 << endl;
    Individu indiv0, indiv1("toto",10,6,1980);
    indiv0.afficher();
    indiv1.afficher();
    indiv0.setIndividu("titi",8,12,1990);
    indiv0.afficher();
    Individu indiv2("toTO",1,2,1988);
    indiv2.afficher(true);

    // TEST CHAINE ETENDUE
    ChaineEtendue che1("bonjour");
    ChaineEtendue che2 = che1, che3 = che1;
    che3.setCharAt(1, 'O');
    if (che1 == che2 && !(che1 == che3))
        cout << "== ChaineEtendue ok" << endl;
    try
    {
        // modifier MAXCAR pour test d'exception sur +
        ChaineEtendue che4("salut");
        ChaineEtendue che5 = che1 + che4;
        cout << che5 << endl;
        cout << che1.indexOf('b') << "," << che1.indexOf('o') << ","
            << che1.indexOf('x') << endl;
        ChaineEtendue che6 = che1.substring(1,4);
        cout << che6 << endl;
        // test exception substring
        int deb, fin;
        cout << "indices sous-chaine : ";
        cin >> deb >> fin;
        cout << che1.substring(deb,fin) << endl;
    }
    catch (ExceptionChaine ex)
    {
        ex.afficher();
    }

   return 0;
}
