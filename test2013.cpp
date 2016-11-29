// test2013.cpp

#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

enum Unite {RAD, DEG};

class Angle
{
public :
    Angle();
    Angle(float val, Unite uniteVal = RAD);
    double getVal(Unite uniteVal = RAD) const;
    void setVal(double val, Unite uniteVal = RAD);
    void afficher(Unite uniteAffichage = RAD);

private :
    double valRad;

    // ces deux fonctions sont statiques car ce sont des utilitaires de calcul
    // qui n'ont pas besoin d'un objet Angle
    static double convertirDegEnRad(double valDegres);
    static double convertirRadEnDeg(double valRadians);

    // réduit la valeur de l'angle à la plage [-PI,+PI]
    void reduirePlageVal();
};

Angle::Angle()
{
    valRad = 0;
}

Angle::Angle(float val, Unite uniteVal)
{
    setVal(val, uniteVal);
}

double Angle::getVal(Unite uniteVal) const
{
    if (uniteVal == RAD)
        return valRad;
    else
        return convertirRadEnDeg(valRad); 
}

void Angle::setVal(double val, Unite uniteVal)
{
    if (uniteVal == RAD)
        valRad = val;
    else
        valRad = convertirDegEnRad(val);
    reduirePlageVal();
}

void Angle::afficher(Unite uniteAffichage)
{
    if (uniteAffichage == RAD)
        cout << valRad << " rad" << endl;
    else
        cout << convertirRadEnDeg(valRad) << " deg" << endl;
}

double Angle::convertirRadEnDeg(double valRadians)
{
    return (valRadians * 180) / M_PI;
}

double Angle::convertirDegEnRad(double valDegres)
{
    return (valDegres * M_PI) / 180;
}

void Angle::reduirePlageVal()
{
    valRad = fmod(valRad, 2*M_PI);
    if (valRad > M_PI)
        valRad -= 2*M_PI;
    else if (valRad < -M_PI)
        valRad += 2*M_PI;
}

class AngleExt : public Angle
{
public :
    AngleExt();
    AngleExt(double val, Unite uniteVal = RAD);
    AngleExt& operator+=(const AngleExt& ang2);
    friend AngleExt operator*(double a, const AngleExt& ang);
    friend ostream& operator<<(ostream& flux, const AngleExt& ang);
    double sinus() const;
    double cosinus() const;
    double tangente() const;
    static AngleExt arcsin(double x);
    static AngleExt arccos(double x);
    static AngleExt arctan(double x);
    static AngleExt arctan2(double y, double x);
};

AngleExt::AngleExt()
    : Angle()
{
}

AngleExt::AngleExt(double val, Unite uniteVal)
    : Angle(val, uniteVal)
{
}

AngleExt& AngleExt::operator+=(const AngleExt& ang2)
{
    setVal(getVal() + ang2.getVal());
    return *this;
}

AngleExt operator*(double a, const AngleExt& ang)
{
    AngleExt angProduit(a * ang.getVal());
    return angProduit;
}

ostream& operator<<(ostream& flux, const AngleExt& ang)
{
    cout << ang.getVal() << " rad";
    return flux;
}

double AngleExt::sinus() const
{
    return sin(getVal());
}

double AngleExt::cosinus() const
{
    return cos(getVal());
}

double AngleExt::tangente() const
{
    return tan(getVal());
}

AngleExt AngleExt::arcsin(double x)
{
    AngleExt angRes(asin(x));
    return angRes;
}

AngleExt AngleExt::arccos(double x)
{
    AngleExt angRes(acos(x));
    return angRes;
}

AngleExt AngleExt::arctan(double x)
{
    AngleExt angRes(atan(x));
    return angRes;
}

AngleExt AngleExt::arctan2(double y, double x)
{
    AngleExt angRes(atan2(y, x));
    return angRes;
}

class Point
{
public :
    Point();
    Point(double x0, double y0);
    Point(double r, const AngleExt& theta);
    double getx() const     { return x; }
    double gety() const     { return y; }
    double getR() const;
    AngleExt getTheta() const;
    void set(double nx, double ny);
    void set(double r, const AngleExt& theta);
    void afficher(bool cartesiennes = true) const;

private :
    double x, y;
};

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double x0, double y0)
{
    x = x0;
    y = y0;
}

Point::Point(double r, const AngleExt& theta)
{
    set(r, theta);
}

double Point::getR() const
{
    return sqrt(x*x + y*y);
}

AngleExt Point::getTheta() const
{
    return AngleExt::arctan2(y, x);
}

void Point::set(double nx, double ny)
{
    x = nx;
    y = ny;
}

void Point::set(double r, const AngleExt& theta)
{
    x = r * theta.cosinus();
    y = r * theta.sinus();
}

void Point::afficher(bool cartesiennes) const
{
    if (cartesiennes)
        cout << "(x=" << x << ", y=" << y << ")" << endl;
    else
        cout << "(r=" << getR() << ", t=" << getTheta() << ")" << endl;
}

class Exception
{
public :
    Exception(const char* m)    { strcpy(msg, m); }
    void afficher() const       { cout << msg << endl; }
private :
    char msg[50];
};

const int MAX_NB_POINTS = 100;

class LignePoly
{
public :
    LignePoly();
    LignePoly(const LignePoly& ligne2);
    ~LignePoly();
    LignePoly& operator=(const LignePoly& ligne2);
    void ajouter(double x, double y);
    void afficher() const;
    double longueur() const;

private :
    Point* points[MAX_NB_POINTS];
    int nbPoints;

    // copie ligne2 dans l'objet courant en allouant les points
    void copier(const LignePoly& ligne2);

    void detruire();
};

// Question 4d : un objet LignePoly contient des points alloués dynamiquement;
// il faut donc écrire un destructeur et, pour que la copie d'objets LignePoly
// soit correcte, il faut écrire le constructeur par copie et l'opérateur =

LignePoly::LignePoly()
{
    nbPoints = 0;
}

LignePoly::LignePoly(const LignePoly& ligne2)
{
    copier(ligne2);
}

LignePoly::~LignePoly()
{
    detruire();
}

LignePoly& LignePoly::operator=(const LignePoly& ligne2)
{
    if (&ligne2 != this) {
        detruire();
        copier(ligne2);
    }
}

void LignePoly::ajouter(double x, double y)
{
    if (nbPoints < MAX_NB_POINTS) {
        points[nbPoints] = new Point(x, y);
        nbPoints++;
    }
    else {
        Exception ex("nb max de points depasse");
        throw ex;
    }
    
}

void LignePoly::afficher() const
{
    for(int i = 0; i < nbPoints; i++)
        points[i]->afficher();
}

double LignePoly::longueur() const
{
    double lg = 0;
    for(int i = 0; i < nbPoints - 1; i++) {
        Point* p1 = points[i];
        Point* p2 = points[i+1];
        double dx = p1->getx() - p2->getx();
        double dy = p1->gety() - p2->gety();
        lg += sqrt(dx*dx + dy*dy);
    }
    return lg;
}

void LignePoly::copier(const LignePoly& ligne2)
{
    for (int i = 0; i < ligne2.nbPoints; i++) {
        Point* pointL2 = ligne2.points[i];
        points[i] = new Point(pointL2->getx(), pointL2->gety());
    }
    nbPoints = ligne2.nbPoints;
}

void LignePoly::detruire()
{
    for (int i = 0; i < nbPoints; i++)
        delete points[i];
}

int main()
{
    cout  << "**** TEST ANGLE ****" << endl;
    Angle a11(1.72), a12(50, DEG), a13(6.45), a14(-9.6);
    cout << a12.getVal(RAD) << endl;
    a11.afficher(DEG);
    a12.afficher(RAD);
    a13.afficher();
    a14.afficher();

    cout  << "**** TEST ANGLEEXT ****" << endl;
    AngleExt a21(1.25) , a22(62, DEG);
    a21 += a22;
    cout << a21 << endl;
    AngleExt a23 = 2.4 * a21;
    cout << a23 << endl;
    double s1 = a21.sinus(), c2 = a22.cosinus(), t3 = a23.tangente();
    cout << s1 << " " << c2 << " " << t3 << endl;
    cout << AngleExt::arcsin(s1) << " " << AngleExt::arccos(c2)
            << " " << AngleExt::arctan(t3) << endl;
    cout << AngleExt::arctan2(-2, -1) << endl;

    cout  << "**** TEST POINT ****" << endl;
    AngleExt a31(60, DEG);
    Point p1(2, a31);
    p1.afficher();
    p1.afficher(false);

    cout  << "**** TEST LIGNEPOLY ****" << endl;
    LignePoly lig1;
    lig1.ajouter(3,4);
    lig1.ajouter(9,2);
    lig1.afficher();
    cout << lig1.longueur() << endl;
    LignePoly lig2(lig1);
    lig2.afficher();
    lig2.ajouter(10,20);
    lig1 = lig2;
    lig1.afficher();
    cout << lig1.longueur() << endl;
    try {
        LignePoly lig3;
        for (int i = 0; i < 2 * MAX_NB_POINTS; i++) {
           lig3.ajouter(i, 2*i);
           cout << "point no " << i  << " ajoute" << endl; 
        }
    }
    catch (Exception e) {
        e.afficher();
    }

    return 0;
}
