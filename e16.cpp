// e16.cpp

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

enum Format {NUM, TEXTE};

class Date
{
public :
    Date (int j, int m, int a);
    string Formater (Format mode, char separ);

private :
    int jour, mois, annee;
};

Date::Date (int j, int m, int a)
{
    jour = j;
    mois = m;
    annee = a;
}

string Date::Formater (Format mode, char separ)
{
    const char* texteMois[] = {"janvier","fevrier","mars","avril","mai","juin",
                "juillet","aout","septembre","octobre","novembre","decembre"};

    ostringstream flot;

	if (mode == NUM)
    {
        flot << setfill('0')
             << setw(2) << jour << separ << setw(2) << mois << separ << annee
             << ends;
    }
    else
    {
        flot << jour << separ << texteMois [mois-1] << separ << annee << ends;
    }

    return flot.str();
}

int main ()
{
    Date da (8,1,2013);

    string s1 = da.Formater (NUM, '/');
    string s2 = da.Formater (TEXTE, ' ');

    cout << s1 << endl;
    cout << s2 << endl;

    return 0;
}
