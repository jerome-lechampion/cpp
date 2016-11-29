// test2012.cpp

#include <iostream>
#include <iomanip>
using namespace std;

class Vecteur
{
public :
    Vecteur(int tval[], int ne);
    Vecteur(int n);
    Vecteur(const Vecteur& v2);
    ~Vecteur();
    Vecteur& operator=(const Vecteur& v2);
    int get_val(int indice) const           { return ptab[indice]; }
    void set_val(int indice, int val)       { ptab[indice] = val; }
    int taille() const                      { return nbe; }
    friend ostream& operator<<(ostream& flux, const Vecteur& v);
private :
    int* ptab;
    int nbe;

    void creerVecteur(int tval[], int ne);
};

Vecteur::Vecteur(int tval[], int ne)
{
    creerVecteur(tval, ne);
}

Vecteur::Vecteur(int n)
{
    ptab = new int[n];
    for (int i = 0; i < n; i++)
        ptab[i] = 0;
    nbe = n;
}

Vecteur::Vecteur(const Vecteur& v2)
{
    creerVecteur(v2.ptab, v2.nbe);
}

Vecteur::~Vecteur()
{
    delete [] ptab;
}

Vecteur& Vecteur::operator=(const Vecteur& v2)
{
    if (this != &v2) {
        delete [] ptab;
        creerVecteur(v2.ptab, v2.nbe);
    }
    return *this;
}

ostream& operator<<(ostream& flux, const Vecteur& v)
{
    flux << "{";
    for (int i = 0; i < v.nbe; i++) {
        flux << v.ptab[i];
        if (i < v.nbe - 1) // une virgule après chaque élément sauf le dernier
            flux << ", ";
    }
    flux << "}";
    return flux;
}

void Vecteur::creerVecteur(int tval[], int ne)
{
    ptab = new int[ne];
    for (int i = 0; i < ne; i++)
        ptab[i] = tval[i];
    nbe = ne;
}

class Vecteur_Creux
{
public :
    Vecteur_Creux(int n = 0);
    Vecteur_Creux(const Vecteur& le_vut, const Vecteur& le_vix, int n);
    Vecteur_Creux Sous_Vecteur(int d) const;
    int taille_r() const        { return nbr; }
    int taille_u() const        { return nbu; }
    friend ostream& operator<<(ostream& flux, const Vecteur_Creux& v);
    friend Vecteur_Creux operator*(int k, const Vecteur_Creux& v);
    Vecteur_Creux operator+(const Vecteur_Creux& v2) const;
private :
    Vecteur vut;
    Vecteur vix;
    int nbr;
    int nbu;
};

// Question 2.4
// Il n'est pas utile d'écrire un constructeur par copie et un opérateur = :
//     1) Ils existent d'office pour toute classe.
//     2) Il est inutile de les réécrire car Vecteur_Creux ne contient aucun
//        pointeur vers de la mémoire allouée spécifiquement pour chaque objet.

// dans les constructeurs de Vecteur_Creux : vut et vix étant des objets
// membres il faut appeler leurs constructeurs dans la liste d'initialisation
//      : vut(...), vix(...)

Vecteur_Creux::Vecteur_Creux(int n)
    : vut(n), vix(n)    // appel du constructeur Vecteur(n) pour vut et vix
{
    nbr = n;
    nbu = 0;
}

Vecteur_Creux::Vecteur_Creux(const Vecteur& le_vut, const Vecteur& le_vix, int n)
    : vut(le_vut), vix(le_vix)  // appel du constructeur par copie pour vut et vit
{
    nbr = n;
    nbu = le_vut.taille();
}

Vecteur_Creux Vecteur_Creux::Sous_Vecteur(int d) const
{
    // pour stocker les indices utiles et les valeurs utiles du sous-vecteur
    int* ixSousVect = new int[nbu];
    int* utSousVect = new int[nbu];

    // parcours des indices utiles du vecteur pour ne garder que ceux < d
    int i = 0;
    while (vix.get_val(i) < d) {
        ixSousVect[i] = vix.get_val(i);
        utSousVect[i] = vut.get_val(i);
        i++;
    }
    int nbuSousVect = i;

    Vecteur vutSousVect(utSousVect, nbuSousVect);
    Vecteur vixSousVect(ixSousVect, nbuSousVect);
    Vecteur_Creux sousVect(vutSousVect, vixSousVect, d);

    delete [] ixSousVect;
    delete [] utSousVect;

    return sousVect;
}

ostream& operator<<(ostream& flux, const Vecteur_Creux& v)
{
    flux << "[";

    int i = 0;    // indice de parcours du vecteur des indices utiles

    for (int ind_reel = 0; ind_reel < v.nbr; ind_reel++) {
        int val_reelle;
        if (ind_reel == v.vix.get_val(i)) {
            val_reelle = v.vut.get_val(i);
            i++;
        }
        else
            val_reelle = 0;
        flux << setw(5) << setfill(' ') << val_reelle;
    }

    flux << "]";
    return flux;
}

Vecteur_Creux operator*(int k, const Vecteur_Creux& v)
{
    Vecteur_Creux vres = v;
    for (int i = 0; i < v.nbu; i++)
        vres.vut.set_val(i, k * v.vut.get_val(i));
    return vres;
}

Vecteur_Creux Vecteur_Creux::operator+(const Vecteur_Creux& v2) const
{
    // pour stocker les indices utiles et les valeurs utiles du vecteur résultat
    int* ixres = new int[nbu + v2.nbu];
    int* utres = new int[nbu + v2.nbu];
    // pour calculer le nb de valeurs utiles du vecteur résultat
    int nbures = 0;

    // on parcourt en parallèle les indices utiles du vecteur 1 (l'objet courant)
    // et du vecteur 2 (v2)
      
    int i1 = 0, i2 = 0; // indices de parcours des vecteurs des indices utiles
    bool finVect1 = false, finVect2 = false;

    while (!finVect1 || !finVect2) {

        int ind_utile1, ind_utile2;
        if (!finVect1)
            ind_utile1 = vix.get_val(i1);
        if (!finVect2)
            ind_utile2 = v2.vix.get_val(i2);

        if ((ind_utile1 < ind_utile2 && !finVect1) || finVect2) {
            ixres[nbures] = ind_utile1;
            utres[nbures] = vut.get_val(i1);
            i1++;
        }
        else if (ind_utile1 == ind_utile2 && !finVect1 && !finVect2) {
            ixres[nbures] = ind_utile1;
            utres[nbures] = vut.get_val(i1) + v2.vut.get_val(i2);
            i1++; i2++;
        }
        else if ((ind_utile2 < ind_utile1 && !finVect2) || finVect1) {
            ixres[nbures] = ind_utile2;
            utres[nbures] = v2.vut.get_val(i2);
            i2++;
        }
        nbures++;
        if (i1 == nbu)
            finVect1 = true;
        if (i2 == v2.nbu)
            finVect2 = true;
    }

    // nb de valeurs réelles du vecteur résultat : max des 2 nb de valeurs réelles
    int nbrres = (nbr > v2.nbr)? nbr : v2.nbr;

    Vecteur vutres(utres, nbures);
    Vecteur vixres(ixres, nbures);
    Vecteur_Creux vres(vutres, vixres, nbrres);

    delete [] ixres;
    delete [] utres;

    return vres;
}

class Matrice_Creuse
{
public :
    Matrice_Creuse(Vecteur_Creux* tVec, int* tInd, int nbut, int nbli);
    Matrice_Creuse(const Matrice_Creuse& m2);
    ~Matrice_Creuse();
    Matrice_Creuse& operator=(const Matrice_Creuse& m2);
    friend ostream& operator<<(ostream& flux, const Matrice_Creuse& m);
    friend Matrice_Creuse operator*(int k, const Matrice_Creuse& m);
    Matrice_Creuse operator+(const Matrice_Creuse& m2);

protected :
    Vecteur_Creux* ligUt;
    int* indUt;
    int nbu, nbLig, nbCol;

private :
    void creerMatrice(Vecteur_Creux* tVec, int* tInd, int nbut, int nbli);
};

Matrice_Creuse::Matrice_Creuse(Vecteur_Creux* tVec, int* tInd, int nbut,
                                int nbli)
{
    creerMatrice(tVec, tInd, nbut, nbli);
}

Matrice_Creuse::Matrice_Creuse(const Matrice_Creuse& m2)
{
    creerMatrice(m2.ligUt, m2.indUt, m2.nbu, m2.nbLig);
}

Matrice_Creuse::~Matrice_Creuse()
{
    delete [] ligUt;
    delete [] indUt;
}

Matrice_Creuse& Matrice_Creuse::operator=(const Matrice_Creuse& m2)
{
    if (this != &m2) {
        delete [] ligUt;
        delete [] indUt;
        creerMatrice(m2.ligUt, m2.indUt, m2.nbu, m2.nbLig);
    }
    return *this;
}

ostream& operator<<(ostream& flux, const Matrice_Creuse& m)
{
    int i = 0;  // indice de parcours des indices utiles

    for (int ind_ligne = 0; ind_ligne < m.nbLig; ind_ligne++) {
        if (ind_ligne == m.indUt[i]) {
            flux << m.ligUt[i];
            i++;
        }
        else {
            Vecteur_Creux ligneNulle(m.nbCol);
            flux << ligneNulle;
        }
        flux << endl;
    }
    return flux;
}

Matrice_Creuse operator*(int k, const Matrice_Creuse& m)
{
    Matrice_Creuse matres = m;
    for (int i = 0; i < m.nbu; i++)
        matres.ligUt[i] = k * m.ligUt[i]; 
    return matres;
}

Matrice_Creuse Matrice_Creuse::operator+(const Matrice_Creuse& m2)
{
    // pour stocker les indices des lignes utiles du résultat
    int* indUtRes = new int[nbu + m2.nbu];
    // pour stocker les lignes utiles du résultat
    Vecteur_Creux* ligUtRes = new Vecteur_Creux[nbu + m2.nbu];
    // pour calculer nb de lignes utiles du résultat
    int nbures = 0;

    // on parcourt en parallèle les indices des lignes utiles de la matrice 1
    // (l'objet courant) et de la matrice 2 (m2)
      
    int i1 = 0, i2 = 0; // indices de parcours des tableaux des indices utiles
    bool finMatrice1 = false, finMatrice2 = false;

    while (!finMatrice1 || !finMatrice2) {

        int ind_utile1, ind_utile2;
        if (!finMatrice1)
            ind_utile1 = indUt[i1];
        if (!finMatrice2)
            ind_utile2 = m2.indUt[i2];

        if ((ind_utile1 < ind_utile2 && !finMatrice1) || finMatrice2) {
            indUtRes[nbures] = ind_utile1;
            ligUtRes[nbures] = ligUt[i1];
            i1++;
        }
        else if (ind_utile1 == ind_utile2 && !finMatrice1 && !finMatrice2) {
            indUtRes[nbures] = ind_utile1;
            ligUtRes[nbures] = ligUt[i1] + m2.ligUt[i2];
            i1++; i2++;
        }
        else if ((ind_utile2 < ind_utile1 && !finMatrice2) || finMatrice1) {
            indUtRes[nbures] = ind_utile2;
            ligUtRes[nbures] = m2.ligUt[i2];
            i2++;
        }
        nbures++;
        if (i1 == nbu)
            finMatrice1 = true;
        if (i2 == m2.nbu)
            finMatrice2 = true;
    }

    Matrice_Creuse matres(ligUtRes, indUtRes, nbures, nbLig);
    delete [] ligUtRes;
    delete [] indUtRes;

    return matres;
}

void Matrice_Creuse::creerMatrice (Vecteur_Creux* tVec, int* tInd, int nbut, int nbli)
{
    ligUt = new Vecteur_Creux[nbut];
    for (int i = 0; i < nbut; i++)
        ligUt[i] = tVec[i];

    indUt = new int[nbut];
    for (int i = 0; i < nbut; i++)
        indUt[i] = tInd[i];

    nbu = nbut;
    nbLig = nbli;
    nbCol = ligUt[0].taille_r(); 
}

class Matrice_Carree : public Matrice_Creuse
{
public :
    Matrice_Carree(const Matrice_Creuse& m);
};

Matrice_Carree::Matrice_Carree(const Matrice_Creuse& m)
    : Matrice_Creuse(m)
{
    // l'appel du constructeur de la classe "mère" Matrice_Creuse a initialisé
    // la matrice avec la même taille et les mêmes valeurs que m, on réduit
    // ensuite la taille de la matrice pour être carrée

    // dimension de la matrice carrée
    int dim = (nbLig < nbCol) ? nbLig : nbCol;

    int i = 0;
    while (indUt[i] < dim) {
        ligUt[i] = ligUt[i].Sous_Vecteur(dim);
        i++;
    }
    nbu = i;
    nbLig = dim;
    nbCol = dim;
}

void f()
{
    int tab[] = {13, -2, 17, -312, 177};
    Vecteur v1(tab, sizeof(tab)/sizeof(int));
    Vecteur v4 = v1;
    v4.set_val(3, 310);
    cout << "v4 : " << v4 << endl;

    Vecteur v5(7);
    cout << "v5(nul) : " << v5 << endl;
    v5 = v1;
    cout << "v5(=v1) : " << v5 << endl;
    cout << "v1 : " << v1 << endl;
}

void g()
{
    int tabix2[] = {1, 3, 6};
    int tabut2[] = {-9, -5, 28};
    Vecteur vut2(tabut2, 3);
    Vecteur vix2(tabix2, 3);
    Vecteur_Creux v2(vut2, vix2, 7);
    cout << "v2:\t" << v2 << endl;
    cout << "taille_r(v2)=" << v2.taille_r() << " taille_u(v2)="
            << v2.taille_u() << endl;
    cout << "v2.sousVect(5) : " << v2.Sous_Vecteur(5) << endl;
    cout << "2*v2:\t" << 2 * v2 << endl;

    int tabut3[] = {11, -612, 403};
    int tabix3[] = {0, 3, 5};
    Vecteur vut3(tabut3, 3);
    Vecteur vix3(tabix3, 3);
    Vecteur_Creux v3(vut3, vix3, 7);
    cout << "v3:\t" << v3 << endl;

    cout << "v2+v3:\t" << v2 + v3 << endl;
    cout << "v3+v2:\t" << v3 + v2 << endl;
    
    cout << endl;
    Vecteur_Creux tabVC1[] = {v3, v2};
    int tabInd1[] = {0, 2};
    Matrice_Creuse m1(tabVC1, tabInd1, 2, 3);
    cout << "m1:" << endl << m1 << endl;

    Matrice_Creuse m10 = m1;
    m10 = 2 * m1;
    cout << "2*m1: " << endl << m10 << endl;

    Vecteur_Creux tabVC2[] = {v2, v3, v2};
    int tabInd2[] = {0, 1, 2};
    Matrice_Creuse m2(tabVC2, tabInd2, 3, 3);
    cout << "m2:" << endl << m2 << endl;
    cout << "m1+m2:" << endl << m1 + m2 << endl;

    Matrice_Carree mc1(m1);
    cout << mc1 << endl;
}

int main (void)
{
    f();
    g();

    return 0;
}
