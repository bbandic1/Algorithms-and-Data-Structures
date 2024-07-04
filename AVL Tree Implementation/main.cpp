#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename tip1, typename tip2> class Mapa {
public:
  Mapa<tip1, tip2>() {}
  virtual ~Mapa<tip1, tip2>() {}
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tip1 &kljuc) = 0;
  virtual tip2 &operator[](tip1 i) = 0;
  virtual const tip2 operator[](tip1 i) const = 0;
};

template <typename tip1, typename tip2>
class BinStabloMapa : public Mapa<tip1, tip2> {
  struct Cvor {
    tip1 kljuc;
    tip2 vr;
    Cvor *roditelj, *lijeva_str, *desna_str;

    Cvor(tip1 k = tip1(), tip2 v = tip2())
        : kljuc(k), vr(v), desna_str(nullptr), lijeva_str(nullptr),
          roditelj(nullptr) {;}
  };      
    Cvor *novi(tip1 k = tip1(), tip2 v = tip2()) {
      Cvor *temp = new Cvor();
      temp->kljuc = k;
      temp->vr = v;
      temp->desna_str = temp->lijeva_str = temp->roditelj = nullptr;
      return temp;
    }
    Cvor *pretraga(Cvor *p, tip1 k) const {
      if (p == nullptr || p->kljuc == k)
        return p;
      if (p->kljuc < k)
        return pretraga(p->desna_str, k);
      else if (p->kljuc > k)
        return pretraga(p->lijeva_str, k);
      return p;
    }
    Cvor *dodaj(Cvor *p, tip1 k, tip2 v = tip2(), Cvor *rod = nullptr) {
      if (p == nullptr) {
        p = novi(k, v);
        p->roditelj = rod;
        return p;
      }
      if (k > p->kljuc)
        p->desna_str = dodaj(p->desna_str, k, v, p);
      else
        p->lijeva_str = dodaj(p->lijeva_str, k, v, p);
      return p;
    }
    Cvor *nasljednik(Cvor *tren) {
      auto temp = tren;
      while (temp && temp->lijeva_str != nullptr)
        temp = temp->lijeva_str;
      return temp;
    }
    void konstruktor(Cvor *x, Cvor *y) {
      if (y == nullptr)
        return;
      konstruktor(x, y->lijeva_str);
      konstruktor(x, y->desna_str);
      dodaj(x, y->kljuc, y->vr);
    }
    Cvor *obrisiC(Cvor *tren, tip1 k) {
      if (tren == nullptr)
        return tren;
      if (k < tren->kljuc)
        tren->lijeva_str = obrisiC(tren->lijeva_str, k);
      else if (k > tren->kljuc)
        tren->desna_str = obrisiC(tren->desna_str, k);
      else {
        if (tren->lijeva_str == nullptr) {
          Cvor *temp = tren->desna_str;
          delete tren;
          return temp;
        } else if (tren->desna_str == nullptr) {
          Cvor *temp = tren->lijeva_str;
          delete tren;
          return temp;
        }
        auto q = nasljednik(tren->desna_str);
        tren->kljuc = q->kljuc;
        tren->vr=q->vr;
        tren->desna_str = obrisiC(tren->desna_str, q->kljuc);
      }
      return tren;
    }
    void obrisi_stablo(Cvor *tren) {

      if (tren == nullptr)
        return;

      obrisi_stablo(tren->lijeva_str);
      obrisi_stablo(tren->desna_str);
      delete tren;
    }

    int ele;
    Cvor *pok;
public:
  BinStabloMapa<tip1, tip2>() : ele(0), pok(nullptr) {;}
  ~BinStabloMapa<tip1, tip2>() {obrisi_stablo(pok);}
  BinStabloMapa<tip1, tip2>(const BinStabloMapa<tip1, tip2> &x) {
    ele = x.ele;
    if (x.ele == 0)
      pok = nullptr;
    else {
      pok = novi(x.pok->kljuc, x.pok->vr);
      konstruktor(pok, x.pok);
    }
  }
  int brojElemenata() const {return ele;}

  void obrisi() {
    obrisi_stablo(pok);
    pok = novi();
    ele = 0;
  }
  void obrisi(const tip1 &k) {
    if (pok->kljuc == k)
      pok = obrisiC(pok, k);
    else
      obrisiC(pok, k);
      ele--;
  }
    BinStabloMapa<tip1, tip2> &operator=(const BinStabloMapa<tip1, tip2> &x) {
    if (this == &x)
      return *this;
    obrisi();
    ele = x.ele;
    if (x.ele == 0)
      pok = nullptr;
    else {
      pok->kljuc=x.pok->kljuc; pok->vr=x.pok->vr;
      konstruktor(pok, x.pok);
    }
    return *this;
  }
  tip2 &operator[](tip1 k) {
    if (pok == nullptr) {
      pok = novi(k);
      ele++;
      return pok->vr;
    }
    auto x = pretraga(pok, k);
    if (x == nullptr) {
      dodaj(pok, k);
      ele++;
      x = pretraga(pok, k);
    }
    return x->vr;
  }
  const tip2 operator[](tip1 k) const {
    auto x = pretraga(pok, k);
    if (x != nullptr)
      return x->vr;
    return tip2();
  }
};
template <typename tip1, typename tip2>
class AVLStabloMapa : public Mapa<tip1, tip2> {

  struct Cvor {

    tip1 kljuc;
    tip2 vrijednost;
    Cvor *l_strana, *d_strana, *roditelj;
    int balans;

    Cvor(tip1 i = tip1(), tip2 u = tip2())
        : kljuc(i), vrijednost(u), d_strana(nullptr), l_strana(nullptr),
          roditelj(nullptr), balans(0) {}
  };

  int balanss(Cvor *t) {
    if (t == nullptr)
      return 0;
    return t->balans;
  }

  int max(int a, int b) { return (a > b) ? a : b; }

  Cvor *novi(tip1 i = tip1(), tip2 u = tip2()) {
    Cvor *temp = new Cvor();
    temp->kljuc = i;
    temp->vrijednost = u;
    temp->d_strana = temp->l_strana = temp->roditelj = nullptr;
    temp->balans = 0;
    return temp;
  }

  void desno_rotiranje(Cvor *t) {

    Cvor *q = nullptr;
    int o = 0;
    q = t->l_strana->d_strana;
    t->balans = 0;
    Cvor *l = t->l_strana;
    Cvor *r = t->roditelj;
    l->roditelj = r;
    l->d_strana = t;

    if (!l->roditelj && !o) {
      p = l;
      o = 1;
    } else if (r->d_strana == t && !o) {
      l->roditelj->d_strana = l;
      o = 1;
    }

    if (o == 0) {
      l->roditelj->l_strana = l;
    }
    l->balans = 0;

    if (q)
      q->roditelj = t;
    t->l_strana = q;
    t->roditelj = l;
  }

  void lijevo_rotiranje(Cvor *t) {

    Cvor *q = nullptr;
    int o = 0;
    q = t->d_strana->l_strana;
    t->balans = 0;
    Cvor *d = t->d_strana;
    Cvor *r = t->roditelj;
    d->roditelj = r;
    d->l_strana = t;

    if (!d->roditelj && !o) {
      p = d;
      o = 1;
    } else if (r->d_strana == t && !o) {
      d->roditelj->d_strana = d;
      o = 1;
    }

    if (o == 0) {
      d->roditelj->l_strana = d;
    }

    d->balans = 0;

    if (q)
      q->roditelj = t;
    t->d_strana = q;
    t->roditelj = d;
  }

  void azurirajBalans(Cvor *t, bool b) {

    if (t == nullptr)
      return;
    else if (b)
      t->balans--;
    else
      t->balans++;

    int blns = t->balans;

    if (t->roditelj) {

      if (t->roditelj->d_strana == t)
        b = true;
      else
        b = false;
    }

    if (blns == 2) {

      if (balanss(t->l_strana) == 1)
        desno_rotiranje(t);
      else {
        lijevo_rotiranje(t->l_strana);
        desno_rotiranje(t);
      }

    } else if (blns == -2) {
      if (balanss(t->d_strana) == -1)
        lijevo_rotiranje(t);

      else {
        desno_rotiranje(t->d_strana);
        lijevo_rotiranje(t);
      }
    } else {

      if (blns == 0)
        return;
      azurirajBalans(t->roditelj, b);
    }
  }

  Cvor *pretraga(Cvor *p, tip1 i) const {
    if (p == nullptr || p->kljuc == i)
      return p;
    if (p->kljuc < i)
      return pretraga(p->d_strana, i);
    else if (p->kljuc > i)
      return pretraga(p->l_strana, i);
    return p;
  }

  Cvor *dodaj(Cvor *p, tip1 i, tip2 u = tip2(), Cvor *rod = nullptr) {

    while (p) {

      if (p->kljuc == i)
        return p;
      else if (i > p->kljuc)
        p = p->d_strana;
      else
        p = p->l_strana;
    }

    if (!p) {

      Cvor *t = AVLStabloMapa::p, *q = nullptr;
      p = novi(i, u);
      while (t) {
        q = t;
        if (t->kljuc > p->kljuc)
          t = t->l_strana;
        else
          t = t->d_strana;
      }

      if (!q)
        AVLStabloMapa::p = p;
      else if (q->kljuc > p->kljuc) {
        q->l_strana = p;
        p->roditelj = q;
      } else {
        q->d_strana = p;
        p->roditelj = q;
      }

      if (!q)
        return p;

      if (q->l_strana && q->d_strana)
        q->balans = 0;
      else {
        bool b = true;
        if (q->l_strana)
          b = false;
        azurirajBalans(q, b);
      }
    }

    return p;
  }

  Cvor *nasljednik(Cvor *t) {
    auto ovaj = t;
    while (ovaj && ovaj->l_strana != nullptr)
      ovaj = ovaj->l_strana;
    return ovaj;
  }

  void konstruktor(Cvor *a, Cvor *b) {

    if (b == nullptr)
      return;

    konstruktor(a, b->l_strana);
    konstruktor(a, b->d_strana);
    dodaj(a, b->kljuc, b->vrijednost);
  }

  void obrisiC(Cvor *t, tip1 i) {

    Cvor *r = nullptr;

    while (t != nullptr && t->kljuc != i) {

      r = t;
      if (t->kljuc < i)
        t = t->d_strana;
      else
        t = t->l_strana;
    }

    if (t == nullptr)
      return;

    Cvor *e, *q, *s ;

    if (!t->l_strana){
      e = t->d_strana;
      s = r;}
    else if (!t->d_strana){
      e = t->l_strana;
      s = r;}
    else {
      e = t->l_strana;
      q = e->d_strana;
      s = t;
      while (q) {
        s = e;
        e = q;
        q = e->d_strana;
      }
      if (t != s) {
        s->d_strana = e->l_strana;
        if (e->l_strana)
          e->l_strana->roditelj = s;
          e->l_strana = t->l_strana;
        if (t->l_strana)
          t->l_strana->roditelj = e;
      }
      e->d_strana = t->d_strana;
      if (t->d_strana)
        t->d_strana->roditelj = e;
    }

    if (!r) {
      AVLStabloMapa::p = e;
    } else {
      if (r->l_strana == t) {
        r->l_strana = e;
        r->balans--;
      } else {
        r->d_strana = e;
        r->balans++;
      }
    }

    if (e)  e->roditelj = r;

      t->d_strana = t->l_strana = t->roditelj = nullptr;
      delete t;
    
  }

  void obrisi_stablo(Cvor *t) {

    if (t == nullptr)
      return;

    obrisi_stablo(t->l_strana);
    obrisi_stablo(t->d_strana);
    delete t;
  }

  int br_ele;
  Cvor *p;

public:

  AVLStabloMapa<tip1, tip2>() : br_ele(0), p(nullptr) {}

  ~AVLStabloMapa<tip1, tip2>() { if(p) obrisi_stablo(p); }

  AVLStabloMapa<tip1, tip2>(const AVLStabloMapa<tip1, tip2> &a) {
    br_ele = a.br_ele;
    if (a.br_ele == 0)
      p = nullptr;

    else {
      p = novi(a.p->kljuc, a.p->vrijednost);
      konstruktor(p, a.p);
    }
  }

  AVLStabloMapa<tip1, tip2> &operator=(const AVLStabloMapa<tip1, tip2> &a) {

    if (this == &a)
      return *this;

    obrisi();
    br_ele = a.br_ele;
    if (a.br_ele == 0)
      p = nullptr;

    else {
      if(!p)p = novi(a.p->kljuc,a.p->vrijednost);
      p->kljuc = a.p->kljuc;
      p->vrijednost = a.p->vrijednost;
      konstruktor(p, a.p);
    }
    return *this;
  }
  
  void Preorder(Cvor *t) const {
    if (t != nullptr) {
      cout << t->kljuc << ",";
      Preorder(t->l_strana);
      Preorder(t->d_strana);
    }
  }

void Preorder() const {
    Preorder(p);
  }
    
  int brojElemenata() const { return br_ele; }

  void obrisi() {
    obrisi_stablo(p);
    p = nullptr;
    br_ele = 0;
  }

  void obrisi(const tip1 &kljuc) {

    obrisiC(p, kljuc);

    br_ele--;
  }

  tip2 &operator[](tip1 i) {

    if (p == nullptr) {
      p = novi(i);
      br_ele++;
      return p->vrijednost;
    }

    auto c = pretraga(p, i);

    if (c == nullptr) {
      dodaj(p, i);
      br_ele++;
      c = pretraga(p, i);
    }

    return c->vrijednost;
  }

  const tip2 operator[](tip1 i) const {
    auto c = pretraga(p, i);
    if (c != nullptr)
      return c->vrijednost;
    return tip2();
  }
};

int main()
{
// Test brisanja
AVLStabloMapa <float, float> m;
m[5] = 5;
m[3] = 3;
m[7] = 7;
m[8] = 8;
m[1] = 1;
m[2] = 2;
m[0.5] = 0.5;
m[4] = 4;
m[1.5] = 1.5;
m[3.5] = 3.5;
m[4.5] = 4.5;

// Proba
cout << std::setprecision(2) << m[4.5] << " ";
// Brisanje slucaj 1
m.obrisi(8);
cout << m[7] << " " << m[8] << " "; 
// Ovim smo ponovo dodali kljuc 8 u mapu
// Brisanje slucaj 2
m[8] = 8;
m.obrisi(7);
cout << m[5] << " " << m[8] << " " << m[7] << " ";
// Brisanje slucaj 3
m.obrisi(3);
cout << m[2] << " " << m[1.5] << " " << m[1] << " ";
cout << m[0.5] << " " << m[3] << " ";
// Brisanje korijena
m.obrisi(5);
m[3] = 3;
cout << m[8] << " " << m[1.5] << " " << m[3];
cout << " " << m[5] << " ";
// Da li je roditelj korektno azuriran?
m.obrisi(7);
cout << m[8] << " " << m[7];
}