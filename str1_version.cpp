// str1.cpp

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
#include "str1.h"

String::String ()
{
    ch = new char[1];
    ch[0] = '\0';
}

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

ostream& operator<< (ostream& flot, const String& str)
{
    flot << str.ch;
    return flot;
}

bool String::operator== (const String& str2) const
{
    return strcmp(ch,str2.ch) == 0;
}

bool String::operator!= (const String& str2) const
{
    return strcmp(ch,str2.ch) != 0;
    // on peut appeler l'operateur == et comparer l'objet courant *this et str2
    // return !(*this == str2);
}

// l'objet courant est la destination de l'affectation
String& String::operator= (const String& str2)
{
    /* on ne fait rien si l'objet courant et str2 representent le meme objet
     * (instruction du style s1 = s1), car dans ce cas ch et str2.ch
     * representent la meme chaine et lorsqu'on detruit ch on detruit aussi
	 * str2.ch
     */
    if (this != &str2)
    {
        /* meme action que le constructeur par copie a une difference pres :
         * l'objet etant deja construit il faut liberer la chaine qui lui a
         * ete precedemment allouee
         */
        delete [] ch;
        ch = new char [strlen(str2.ch) + 1];
        strcpy (ch, str2.ch);
    }

    return *this;
}

String String::operator+ (const String& str2) const
{
    /* fabrication d'une chaine egale a la concatenation des chaines presentes
     * dans les 2 objets String a additionner
     */
    char* chResult = new char [strlen(ch) + strlen(str2.ch) + 1];
    strcpy (chResult, ch);
    strcat (chResult, str2.ch);

    // a partir de cette chaine, construction de l'objet String resultat
    String strResult (chResult);
    delete [] chResult;

    return strResult;
}

String& String::operator+= (const String& str2)
{
    // on appelle l'operateur d'addition precedent en faisant :
    //      objet_courant = objet_courant + str2
    *this = *this + str2;

    return *this;
}

bool String::operator<= (const String& str2) const
{
    return strstr (str2.ch, ch) != NULL;
}
