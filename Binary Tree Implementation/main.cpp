#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>

using namespace std;

template <typename tip1, typename tip2> class Mapa {

public:
  Mapa<tip1, tip2>() {;}
  virtual ~Mapa<tip1, tip2>() {;}
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tip1 &kljuc) = 0;
  virtual tip2 &operator[](tip1 i) = 0;
  virtual const tip2 operator[](tip1 i) const = 0;
};

template <typename tip1, typename tip2>
class NizMapa : public Mapa<tip1, tip2> {
protected:
  int vel, ele;
  std::pair<tip1, tip2> **pok;

public:
  NizMapa<tip1, tip2>()
      : Mapa<tip1, tip2>(), pok(new std::pair<tip1, tip2> *[100000]()),
        vel(100000), ele(0) {}
  ~NizMapa<tip1, tip2>() {
    for (int i = 0; i < ele; i++)
      delete pok[i];
    delete[] pok;
  }
  NizMapa<tip1, tip2>(const NizMapa<tip1, tip2> &x) {
    ele = x.ele;
    vel = x.velicina;
    if (x.velicina == 0)
      pok = nullptr;
    else {
      pok = new std::pair<tip1, tip2> *[vel]();
      for (int i = 0; i < x.ele; i++) {
        pok[i] = new std::pair<tip1, tip2>(*x.p[i]);
      }
    }
  }
  void obrisi() {
    if (ele == 0)
      throw std::range_error("Nema elemenata");
    for (int i = 0; i < ele; i++)
      delete pok[i];
    ele = 0;
  }
  void obrisi(const tip1 &kljuc) {
    for (int i = 0; i < ele; i++)
      if (pok[i]->first == kljuc) {
        delete pok[i];
        for (int j = i; j < ele - 1; j++)
          pok[j] = pok[j + 1];
        pok[ele] = nullptr;
        ele--;
        return;
      }
    throw std::range_error("Nema kljuca");
  }

  int brojElemenata() const { return ele;}
  int Velicina() const { return vel; }

  tip2 &operator[](tip1 kljuc) {
    if (ele == vel) {
      std::pair<tip1, tip2> **temp =
          new std::pair<tip1, tip2> *[10000 + vel]();
      for (int i = 0; i < ele; i++) {
        temp[i] = new std::pair<tip1, tip2>(*pok[i]);
        delete pok[i];
      }
      delete[] pok;
      vel = vel + 10000;
      pok = temp;
      temp = nullptr;
    }
    for (int i = 0; i < ele; i++)
      if (pok[i]->first == kljuc)
        return pok[i]->second;
    pok[ele] = new std::pair<tip1, tip2>(kljuc, tip2());
    ele++;
    return pok[ele - 1]->second;
  }
  const tip2 operator[](tip1 kljuc) const {
    for (int i = 0; i < ele; i++)
      if (pok[i]->first == kljuc)
        return pok[i]->second;

    return tip2();
  }
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

int main() {
BinStabloMapa <float, float> m;
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