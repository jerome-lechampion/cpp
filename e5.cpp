// e5.cpp

#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

class String
{
public :
    String (const char* ch2);
    String (const String& objSource);
    ~String ();
    void afficher () const;
    void changerEnMaj ();
    bool estEgal (const String& str2) const;

private :
    char* ch;
};

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

int main ()
{
    String s1("salut");
    String s2 = s1;
    s1.afficher();
    s2.afficher();

    cout << "apres passage de s2 en majuscules :" << endl;
    s2.changerEnMaj();
    s1.afficher();
    s2.afficher();

    String s3("salut"), s4("salux");
    if (s1.estEgal(s3) && !s1.estEgal(s4))
        cout << "estEgal ok" << endl;

    /* meme si elle est declaree devant recevoir un objet String en parametre
     * on peut passer a la fonction estEgal un char*, car celui-ci est
     * automatiquement converti en un objet String grace au constructeur
     * String(const char*)
     */
    if (s1.estEgal("salut"))
        cout << "conversion char* => String : ok" << endl;

    return 0;
}

