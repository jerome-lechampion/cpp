// str.h

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

