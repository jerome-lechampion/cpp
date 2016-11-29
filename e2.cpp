// e2.cpp

#include <iostream>
#include <cstring>
using namespace std;

char* cat (const char* ch1, const char* ch2);
void inv (char* ch);

char* cat (const char* ch1, const char* ch2)
{
    // allocation de la chaine resultat dans laquelle on copiera ch1, puis a
    // laquelle on concatenera ch2
    char* chResult = new char [strlen(ch1) + strlen(ch2) + 1];

    strcpy (chResult, ch1);
    strcat (chResult, ch2);

    return chResult;
}

void inv (char* ch)
{
    int lg = strlen(ch);

    // allocation d'une chaine de travail dans laquelle on transferera en sens
    // inverse les octets de ch et qu'on recopiera dans ch
    char* chInverse = new char [lg + 1];

    for (int i = 0; i < lg; i++)
        chInverse[i] = ch[lg - i - 1];

    chInverse[lg] = 0;

    strcpy (ch, chInverse);
    delete [] chInverse;
}

int main ()
{
    char* chaine1 = cat ("xyz", "abcd");
    cout << chaine1 << endl;
    delete [] chaine1;

    char chaine2[100];
    cout << "chaine a inverser : ";
    cin >> chaine2;
    inv (chaine2);
    cout << chaine2 << endl;

    return 0;
}

