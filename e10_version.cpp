// e10.cpp

#include <iostream>
using namespace std;

class Point
{
public :
    Point (float x0, float y0)
        { x= x0; y = y0; }

    float getX () const       { return x; }
    float getY () const       { return y; }

    void setX (float nx)      { x = nx; }
    void setY (float ny)      { y = ny; }

private :
    float x, y;
};

class Segment
{
public :
    Segment (const Point& a, const Point& b);
    void translation (const Point& nouvOrg);
    void afficher () const;

    friend bool operator== (const Segment& seg1, const Segment& seg2);
    bool operator!= (const Segment& seg2) const;
    friend ostream& operator<< (ostream& flot, const Segment& seg);

private :
    Point org, ext;
};

/* dans la liste d'initialisation, appel des constructeurs des objets membres
org et ext
1ere version : pour org et ext, appel du constructeur Point(int,int)
2eme version : pour org et ext, appel du constructeur par copie de Point
*/
Segment::Segment (const Point& a, const Point& b)
    : org (a.getX(),a.getY()), ext (b.getX(),b.getY())
    //: org(a), ext(b)    // 2eme version
{
}

void Segment::translation (const Point& nouvOrg)
{
    // calcul des deplacements sur x et sur y
    float dx = nouvOrg.getX() - org.getX();
    float dy = nouvOrg.getY() - org.getY();

    org.setX (nouvOrg.getX());
    org.setY (nouvOrg.getY());

    ext.setX (ext.getX() + dx);
    ext.setY (ext.getY() + dy);

    /* si setX et setY n'existaient pas, on aurait pu modifier org et ext
     * ainsi :
    org = nouvOrg;
    Point nouvExt (ext.getX() + dx, ext.getY() + dy);
    ext = nouvExt;
    */
}

void Segment::afficher () const
{
    cout << "origine(" << org.getX() << "," << org.getY() << ")"
    	<< ", extremite(" << ext.getX() << "," << ext.getY() << ")" << endl;
}

bool operator== (const Segment& seg1, const Segment& seg2)
{
    return seg1.org.getX() == seg2.org.getX()
        && seg1.org.getY() == seg2.org.getY()
        && seg1.ext.getX() == seg2.ext.getX()
        && seg1.ext.getY() == seg2.ext.getY();
}

bool Segment::operator!= (const Segment& seg2) const
{
    // on appelle l'operateur "==" applique a l'objet courant et seg2
    return !(*this == seg2);
}

ostream& operator<< (ostream& flot, const Segment& seg)
{
    flot << "segment (" << seg.org.getX() << "," << seg.org.getY() << ")"
         << "->("       << seg.ext.getX() << "," << seg.ext.getY() << ")";

    return flot;
}

int main ()
{
    // test des operateurs

    Point P(2,4), Q(9,6), R(9,6), S(8,6);
    Segment S1(P,Q), S2(P,R), S3(P,S);

    cout << S1 << "  " << S2  << "  " << S3 << endl;

    if (S1 == S2 && S1 != S3)
        cout << "comparaisons ok" << endl;

    return 0;
}
