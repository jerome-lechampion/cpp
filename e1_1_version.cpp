// e1_1.cpp

#include <iostream>
using namespace std;

struct Date
{
    int jour, mois, annee;
};

const int ANNEE_BASE = 2000;

void init (Date& dat, int j, int m, int a = ANNEE_BASE);
void afficher (const Date& dat);
int comparer (const Date& dat1, const Date& dat2);
int comparer (const Date& dat, int j, int m, int a);

void init (Date& dat, int j, int m, int a)
{
    dat.jour = j;
    dat.mois = m;
    dat.annee = a;
}

void afficher (const Date& dat)
{
    cout << dat.jour << "/" << dat.mois << "/" << dat.annee << endl;
}

int comparer (const Date& dat1, const Date& dat2)
{
    int result;

    if (dat1.annee > dat2.annee)
        result = 1;
    else if (dat1.annee < dat2.annee)
        result = -1;

    // annees egales
    else if (dat1.mois > dat2.mois)
        result = 1;
    else if (dat1.mois < dat2.mois)
        result = -1;

    // annees et mois egaux
    else if (dat1.jour > dat2.jour)
        result = 1;
    else if (dat1.jour < dat2.jour)
        result = -1;

    // annees, mois et jours egaux
    else
        result = 0;

    return result;
}

int comparer (const Date& dat, int j, int m, int a)
{
    // on appelle l'autre fonction comparer
    Date d2;
    init (d2, j, m, a);
    return comparer (dat, d2);
}

int main ()
{
    int j1, m1, j2, m2, a2;

    cout << "saisir jour/mois de annee ref: ";
    cin >> j1 >> m1;
    cout << "saisir une date : ";
    cin >> j2 >> m2 >> a2;

    Date date1, date2;
    init (date1, j1, m1);
    init (date2, j2, m2, a2);

    afficher (date1);
    afficher (date2);

    cout << "comparer date1/date2 : " << comparer (date1,date2) << endl;
    cout << "comparer date1/entiers : " << comparer (date1,j2,m2,a2) << endl;

    return 0;
}
