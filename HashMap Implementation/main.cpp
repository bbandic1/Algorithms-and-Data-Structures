#include <exception>
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
          roditelj(nullptr) {
      ;
    }
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
      tren->vr = q->vr;
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
  BinStabloMapa<tip1, tip2>() : ele(0), pok(nullptr) { ; }
  ~BinStabloMapa<tip1, tip2>() { obrisi_stablo(pok); }
  BinStabloMapa<tip1, tip2>(const BinStabloMapa<tip1, tip2> &x) {
    ele = x.ele;
    if (x.ele == 0)
      pok = nullptr;
    else {
      pok = novi(x.pok->kljuc, x.pok->vr);
      konstruktor(pok, x.pok);
    }
  }
  int brojElemenata() const { return ele; }

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
      pok->kljuc = x.pok->kljuc;
      pok->vr = x.pok->vr;
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
class HashMapa : public Mapa<tip1, tip2> {
protected:
  int velicina, br_ele;
  std::pair<tip1, tip2> **p;
  bool *prazno;
  unsigned int (*funkcija)(tip1, unsigned int);

public:
  HashMapa<tip1, tip2>()
      : Mapa<tip1, tip2>(), p(new std::pair<tip1, tip2> *[100000]()),
        velicina(100000), br_ele(0), prazno(new bool[100000]),
        funkcija(nullptr) {
    for (int i = 0; i < 100000; i++)
      prazno[i] = false;
  }

  ~HashMapa<tip1, tip2>() {
    if (p) {
      for (int i = 0; i < velicina; i++)
        delete p[i];
      delete[] p;
    }

    if (prazno)
      delete[] prazno;
  }

  HashMapa<tip1, tip2>(const HashMapa<tip1, tip2> &a) {

    br_ele = a.br_ele;
    velicina = a.velicina;
    funkcija = a.funkcija;
    prazno = new bool[velicina];

    if (a.velicina == 0) {
      p = nullptr;
      for (int i = 0; i < velicina; i++)
        prazno[i] = false;
    }

    else {
      p = new std::pair<tip1, tip2> *[velicina]();

      for (int i = 0; i < a.velicina; i++) {
        if (a.p[i])
          p[i] = new std::pair<tip1, tip2>(*a.p[i]);
        prazno[i] = a.prazno[i];
      }
    }
  }

  HashMapa<tip1, tip2> &operator=(const HashMapa<tip1, tip2> &a) {

    if (this == &a)
      return *this;

    if (a.Velicina() > Velicina())
      prosiri(a.velicina);

    for (int i = 0; i < Velicina(); i++)
      prazno[i] = false;

    br_ele = a.br_ele;
    funkcija = a.funkcija;

    for (int i = 0; i < a.velicina; i++) {
      if (a.p[i]) {
        delete p[i];
        p[i] = new std::pair<tip1, tip2>(*a.p[i]);
      }
      prazno[i] = a.prazno[i];
    }

    return *this;
  }

  void prosiri(int a = 10000) {
    std::pair<tip1, tip2> **temp = new std::pair<tip1, tip2> *[a + velicina]();
    bool *q = new bool[a + velicina]();

    for (int i = 0; i < velicina; i++) {
      if (p[i])
        temp[i] = new std::pair<tip1, tip2>(*p[i]);
      delete p[i];
      q[i] = prazno[i];
    }
    for (int i = 0; i < a; i++)
      q[velicina + i] = false;

    delete[] p;
    delete[] prazno;
    velicina += a;
    p = temp;
    prazno = q;
  }

  void obrisi() {
    if (br_ele == 0)
      throw std::range_error("Nema elemenata");

    for (int i = 0; i < velicina; i++)

      prazno[i] = false;

    br_ele = 0;
  }

  void obrisi(const tip1 &kljuc) {

    for (int i = 0; i < velicina; i++)
      if (p[i] && p[i]->first == kljuc) {
        prazno[i] = false;

        br_ele--;
        return;
      }

    throw std::range_error("Nema kljuca");
  }

  int brojElemenata() const { return br_ele; }
  int Velicina() const { return velicina; }

  bool UmetniHash(const tip1 &k) {

    int j, i = 1;
    do {

      do {
        j = funkcija(k, i);
        if (prazno[j] == false) {

          delete p[j];
          p[j] = new std::pair<tip1, tip2>(k, tip2());
          prazno[j] = true;

          return true;
        } else
          i = i + 1;
      } while (i < velicina);

      prosiri();

    } while (velicina < 100000000);

    return false;
  }

  int TraziHash(const tip1 &k) const {
    int indeks, i(1);
    do {
      indeks = funkcija(k, i);
      if (prazno[indeks] && p[indeks]->first == k)
        return indeks;
      else
        i = i + 1;
    } while ((prazno[indeks] == true && i != velicina) ||
             prazno[funkcija(k, i)] == true);

    return -1;
  }

  tip2 &operator[](tip1 kljuc) {

    if (!funkcija) {
      throw std::bad_exception();
    }
    
    if (br_ele == velicina)
      prosiri();

    int in = funkcija(kljuc, velicina);
    if (!prazno[in]) {
      delete p[in];
      p[in] = new std::pair<tip1, tip2>(kljuc, tip2());
      br_ele++;
      prazno[in] = true;
      return p[in]->second;
    }
    if (prazno[in] && p[in]->first == kljuc)
      return p[in]->second;
    else {
      in = TraziHash(kljuc);
      if (in == -1) {
        UmetniHash(kljuc);
        br_ele++;
        in = TraziHash(kljuc);
        prazno[in] = true;
      }
    }

    return p[in]->second;
  }

  const tip2 operator[](tip1 kljuc) const {
    if (!funkcija)
      return tip2();

    int in = funkcija(kljuc, velicina);
    if (prazno[in] && p[in] && p[in]->first == kljuc)
      return p[in]->second;
    else {
      in = TraziHash(kljuc);
      if (in == -1)
        return tip2();
    }

    return p[in]->second;
  }

  void definisiHashFunkciju(unsigned int (*func)(tip1, unsigned int)) {
    funkcija = func;
    return;
  }
};

unsigned int mojHash(int ulaz, unsigned int max) { return ulaz % max; }

bool UmetniHash(std::vector<int> &a, const int &k) {

  int i = 1;

  int j = mojHash(k, a.size());

  if (a[j] == 0 || a[j] == -1) {

    a[j] = k;
    int l = 0;
    for (int i = 0; i < a.size(); i++)
      if (a[i] != 0 && a[i] != -1)
        l++;

    if (l == a.size())
      a.resize(a.size() + 3, 0);

    return true;
  }

  j = mojHash(k, i);
  do {

    if (a[j] == 0 || a[j] == -1) {

      a[j] = k;

      int l = 0;
      for (int i = 0; i < a.size(); i++)
        if (a[i] != 0 && a[i] != -1)
          l++;
      if (l == a.size())
        a.resize(a.size() + 3, 0);

      return true;
    } else
      j = j + 1;
    if (j == a.size())
      j = 0;

  } while (j < a.size());

  return false;
}

int main() {
  HashMapa<std::string, std::string> m;
  // Nije definisana hash funkcija!
  std::string s1("Sarajevo"), s2("Zagreb");
  m[s1] = "BiH";
  m[s2] = "Hrvatska";
  std::cout << m.brojElemenata() << " " << m[s2];
  return 0;
}