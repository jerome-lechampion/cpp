// str.cpp

#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;
#include "str.h"

String::String (const char* ch2)
{
    ch = new char [strlen(ch2) + 1];
    strcpy (ch, ch2);
}

String::String (const String& objSource)
{
    ch = new char [strlen(objSource.ch) + 1];
    strcpy (ch, objSource.ch);
}

/* lorsque l'objet sera detruit il faudra liberer la zone qui lui a ete allouee
 * => necessite d'ecrire un destructeur
 */
String::~String ()
{
    delete [] ch;
}

void String::afficher () const
{
    cout << ch << endl;
}

void String::changerEnMaj ()
{
    int i = 0;

    while (ch[i] != 0)
    {
        ch[i] = toupper(ch[i]);
        i++;
    }
}

bool String::estEgal (const String& str2) const
{
    bool egalite;

    if (strcmp(ch,str2.ch) == 0)
        egalite = true;
    else
        egalite = false;

    return egalite;
}

