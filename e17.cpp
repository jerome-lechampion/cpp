// e17.cpp

#include <iostream>
#include <cmath>
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

    double longueur () const;

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

double Segment::longueur () const
{
    double dx = ext.getX() - org.getX();
    double dy = ext.getY() - org.getY();
    return sqrt (dx * dx + dy * dy);
}

class Forme
{
public :
    virtual double perimetre () const = 0;
    virtual double surface () const = 0;
    virtual void afficher () const = 0;

    Forme* suiv;
};

class Cercle : public Forme
{
public :
    Cercle (const Point& cen, double ray);
    double perimetre () const;
    double surface () const;
    void afficher () const;

private :
    Point centre;
    double rayon;
};

/* dans la liste d'initialisation on appelle le constructeur de l'objet membre
 * centre
 */
Cercle::Cercle (const Point& cen, double ray)
    : centre(cen.getX(),cen.getY())
{
    rayon = ray;
}

double Cercle::perimetre () const
{
    return 3.14 * 2 * rayon;
}

double Cercle::surface () const
{
    return 3.14 * rayon * rayon;
}

void Cercle::afficher () const
{
    cout << "cercle de perimetre " << perimetre() << " et de surface "
	                                                << surface() << endl;
}

class Rectangle : public Forme
{
public :
    Rectangle (const Segment& segLarg, double haut);
    double perimetre () const;
    double surface () const;
    void afficher () const;

private :
    Segment segLargeur;
    double hauteur;
};

/* dans la liste d'initialisation on appelle le constructeur de l'objet membre
 * segLargeur (constructeur par copie de Segment)
 */
Rectangle::Rectangle (const Segment& segLarg, double haut)
    : segLargeur(segLarg)
{
    hauteur = haut;
}

double Rectangle::perimetre () const
{
    return 2 * (segLargeur.longueur() + hauteur);
}

double Rectangle::surface () const
{
    return segLargeur.longueur() * hauteur;
}

void Rectangle::afficher () const
{
    cout << "rectangle de perimetre " << perimetre() << " et de surface "
	                                                << surface() << endl;
}

/* la classe Carre herite des fonctions perimetre, surface et afficher de
 * Rectangle et a besoin de redefinir seulement afficher
 */
class Carre : public Rectangle
{
public :
    Carre (const Segment& cote);
    void afficher () const;
};

/* dans la liste d'initialisation on appelle le constructeur de la classe mere
 * Rectangle
 */
Carre::Carre (const Segment& cote) 
    : Rectangle (cote, cote.longueur())
{
}

void Carre::afficher () const
{
    cout << "carre de perimetre " << perimetre() << " et de surface "
	                                                << surface() << endl;
}

class ListeFormes
{
    Forme* racine;

public :
    ListeFormes ();
    void chainer (Forme* pForme);
    void afficherMax () const;
};

ListeFormes::ListeFormes ()
{
    racine = 0;    // liste vide
}

void ListeFormes::chainer (Forme* pForme)
{
    // chainage en tete de liste de l'objet pointe par pForme
    pForme->suiv = racine;
    racine = pForme;
}

void ListeFormes::afficherMax () const
{
    double maxPerim = 0, maxSurf = 0;
    Forme *pMaxPerim = 0;
    Forme *pMaxSurf = 0;

    Forme* p = racine;

    /* parcours du chainage */
    while (p != 0)
    {
        //p->afficher();
        if (p->perimetre() >= maxPerim)
        {
            pMaxPerim = p;
            maxPerim = p->perimetre();
        }
        if (p->surface() >= maxSurf)
        {
            pMaxSurf = p;
            maxSurf = p->surface();
        }
        p = p->suiv;
    }

    if (pMaxPerim != 0)
    {
        cout << "perimetre max = " << maxPerim << " par ";
        pMaxPerim->afficher();
    }
    if (pMaxSurf != 0)
    {
        cout << "surface max = " << maxSurf << " par ";
        pMaxSurf->afficher();
    }
}

int main ()
{
    Point P1(12,6), P2(15,6);

    Cercle ce (P1,3.2);
    ce.afficher();

    Segment Sa(P1,P2);

    Rectangle re (Sa,8);
    re.afficher();

    Carre ca (Sa);
    ca.afficher();

    cout << "LISTE DE FORMES :" << endl;
    ListeFormes lf;
    lf.chainer (&ce);
    lf.chainer (&re);
    lf.chainer (&ca);
    lf.afficherMax();

    return 0;
}
