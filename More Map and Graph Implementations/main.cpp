#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

template <typename tip1, typename tip2> class Mapa {
public:
  Mapa<tip1, tip2>() { ; }
  virtual ~Mapa<tip1, tip2>() { ; }
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tip1 &kljuc) = 0;
  virtual tip2 &operator[](tip1 x) = 0;
  virtual const tip2 operator[](tip1 x) const = 0;
};

template <typename tip1, typename tip2>
class NizMapa : public Mapa<tip1, tip2> {
protected:
  int vel, el;
  std::pair<tip1, tip2> **pok;

public:
  NizMapa<tip1, tip2>()
      : Mapa<tip1, tip2>(), pok(new std::pair<tip1, tip2> *[33333]()),
        vel(33333), el(0) {
    ;
  }
  ~NizMapa<tip1, tip2>() {
    for (int i = 0; i < el; i++)
      delete pok[i];
    delete[] pok;
  }

  NizMapa<tip1, tip2>(const NizMapa<tip1, tip2> &x) {
    el = x.el;
    vel = x.vel;
    if (x.vel == 0)
      pok = nullptr;
    else {
      pok = new std::pair<tip1, tip2> *[vel]();
      for (int i = 0; i < x.el; i++)
        pok[i] = new std::pair<tip1, tip2>(*x.pok[i]);
    }
  }
  int brojElemenata() const { return el; }
  int Velicina() const { return vel; }
  void obrisi() {
    if (el == 0)
      throw std::range_error("Nema elemenata");
    for (int i = 0; i < el; i++)
      delete pok[i];
    el = 0;
  }
  void obrisi(const tip1 &kljuc) {
    for (int i = 0; i < el; i++)
      if (pok[i]->first == kljuc) {
        delete pok[i];
        for (int j = i; j < el - 1; j++)
          pok[j] = pok[j + 1];
        pok[el] = nullptr;
        el--;
        return;
      }
    throw std::logic_error("Nema kljuca");
  }
  NizMapa<tip1, tip2> &operator=(const NizMapa<tip1, tip2> &x) {
    if (this == &x)
      return *this;
    obrisi();
    el = x.el;
    if (x.Velicina() > Velicina()) {
      delete[] pok;
      pok = new std::pair<tip1, tip2> *[vel + x.Velicina()]();
      vel = vel + x.vel;
    }
    for (int i = 0; i < x.el; i++) {
      pok[i] = new std::pair<tip1, tip2>(*x.pok[i]);
    }
    return *this;
  }
  tip2 &operator[](tip1 kljuc) {
    if (el == vel) {
      std::pair<tip1, tip2> **temp = new std::pair<tip1, tip2> *[33333 + vel]();
      for (int i = 0; i < el; i++) {
        temp[i] = new std::pair<tip1, tip2>(*pok[i]);
        delete pok[i];
      }
      delete[] pok;
      vel = vel + 33333;
      pok = temp;
      temp = nullptr;
    }
    for (int i = 0; i < el; i++) {
      if (pok[i]->first == kljuc)
        return pok[i]->second;
    }
    pok[el] = new std::pair<tip1, tip2>(kljuc, tip2());
    el++;
    return pok[el - 1]->second;
  }
  const tip2 operator[](tip1 kljuc) const {
    for (int i = 0; i < el; i++)
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
class HashMapaLan : public Mapa<tip1, tip2> {
protected:
  int br_ele;
  std::vector<std::list<std::pair<tip1, tip2> *>> p;
  unsigned int (*funkcija)(tip1, unsigned int);

public:
  HashMapaLan<tip1, tip2>() : Mapa<tip1, tip2>(), br_ele(0), funkcija(nullptr) {
    p.resize(10000);
  }

  ~HashMapaLan<tip1, tip2>() { obrisi(); }

  HashMapaLan<tip1, tip2>(const HashMapaLan<tip1, tip2> &a) {

    br_ele = a.br_ele;
    funkcija = a.funkcija;

    for (int i = 0; i < a.p.size(); i++) {

      p.push_back(std::list<std::pair<tip1, tip2> *>());
      auto it = a.p[i].begin();
      while (it != a.p[i].end()) {
        p[i].push_back(new std::pair<tip1, tip2>((*it)->first, (*it)->second));
        it++;
      }
    }
  }

  HashMapaLan<tip1, tip2> &operator=(const HashMapaLan<tip1, tip2> &a) {

    if (this == &a)
      return *this;

    obrisi();

    while (p.size() < a.p.size())
      p.push_back(std::list<std::pair<tip1, tip2> *>());

    br_ele = a.br_ele;
    funkcija = a.funkcija;

    for (int i = 0; i < a.p.size(); i++) {

      auto it = a.p[i].begin();
      while (it != a.p[i].end()) {
        p[i].push_back(new std::pair<tip1, tip2>((*it)->first, (*it)->second));
        it++;
      }
    }

    return *this;
  }

  void obrisi() {

    if (!funkcija)
      throw std::domain_error("Hash funkcija?");
    if (br_ele == 0)
      throw std::domain_error("Nema elemenata");

    for (int i = 0; i < p.size(); i++) {

      auto it = p[i].begin();
      while (it != p[i].end()) {
        delete *it;
        it++;
      }

      p[i].resize(0);
    }

    br_ele = 0;
  }

  void obrisi(const tip1 &kljuc) {

    if (!funkcija)
      throw std::domain_error("Hash funkcija?");

    int in = funkcija(kljuc, p.size());
    typename std::list<std::pair<tip1, tip2> *>::iterator it = p[in].begin();

    while (it != p[in].end()) {

      if ((*it)->first == kljuc) {
        delete *it;
        p[in].erase(it);
        br_ele--;
        return;
      }
      it++;
    }

    throw std::logic_error("Nema kljuca");
  }

  int brojElemenata() const { return br_ele; }

  int TraziHash(const tip1 &k) const {

    int in = funkcija(k, p.size());
    typename std::list<std::pair<tip1, tip2> *> l = p[in];
    typename std::list<std::pair<tip1, tip2> *>::iterator it = l.begin();
    int i = 0;

    while (it != l.end()) {

      if ((*it)->first == k)
        return i;

      i++;
      it++;
    }

    return -1;
  }

  tip2 &operator[](tip1 kljuc) {

    if (!funkcija)
      throw std::domain_error("Hash funkcija?");

    int in = funkcija(kljuc, p.size());
    typename std::list<std::pair<tip1, tip2> *>::iterator it = p[in].begin();

    if (p[in].empty()) {
      p[in].push_back(new std::pair<tip1, tip2>(kljuc, tip2()));
      br_ele++;
      it = p[in].begin();
      return (*it)->second;
    }

    if ((*it)->first == kljuc)
      return (*it)->second;
    else {
      int q = TraziHash(kljuc);
      if (q == -1) {
        br_ele++;
        p[in].push_back(new std::pair<tip1, tip2>(kljuc, tip2()));
        p[in].sort([](const std::pair<tip1, tip2> *a,
                      const std::pair<tip1, tip2> *b) -> bool {
          return a->first < b->first;
        });
        q = TraziHash(kljuc);
        it = p[in].begin();
      }
      while (q > 0) {
        it++;
        q--;
      }
    }

    return (*it)->second;
  }

  const tip2 operator[](tip1 kljuc) const {

    if (!funkcija)
      throw std::domain_error("Hash funkcija?");

    int in = funkcija(kljuc, p.size());
    typename std::list<std::pair<tip1, tip2> *> l = p[in];
    typename std::list<std::pair<tip1, tip2> *>::iterator it = l.begin();

    if (!p[in].empty() && (*it)->first == kljuc)
      return (*it)->second;

    else if (p[in].empty())
      return tip2();
    else {
      in = TraziHash(kljuc);
      if (in == -1)
        return tip2();
      else
        while (in > 0) {
          it++;
          in--;
        }
    }

    return (*it)->second;
  }

  void definisiHashFunkciju(unsigned int (*func)(tip1, unsigned int)) {
    funkcija = func;
    return;
  }
};

template <typename tip> class GranaIterator;
template <typename tip> class Grana;
template <typename tip> class Cvor;
template <typename tip> class ListaGraf;

template <typename tip> class UsmjereniGraf {
public:
  UsmjereniGraf() {}
  UsmjereniGraf(int a) {}
  virtual ~UsmjereniGraf() {}

  virtual int dajBrojCvorova() const = 0;
  virtual void postaviBrojCvorova(int a) = 0;
  virtual void dodajGranu(int p, int d, float t) = 0;
  virtual void obrisiGranu(int p, int d) = 0;
  virtual bool postojiGrana(int p, int d) = 0;
  virtual void postaviTezinuGrane(int p, int d, float t) = 0;
  virtual tip dajOznakuGrane(int p, int d) = 0;
  virtual tip dajOznakuCvora(int b) = 0;
  virtual float dajTezinuGrane(int p, int d) = 0;
  virtual void postaviOznakuCvora(int b, tip a) = 0;
  virtual void postaviOznakuGrane(int p, int d, tip a) = 0;
  Grana<tip> dajGranu(int p, int d) { return Grana<tip>(this, p, d); }
  Cvor<tip> dajCvor(int b) { return Cvor<tip>(this, b); }

  GranaIterator<tip> dajGranePocetak() {
    GranaIterator<tip> it(this, 0, -1);
    return ++it;
  }

  GranaIterator<tip> dajGraneKraj() {
    GranaIterator<tip> it(this, -1, -1);
    return it;
  }
  virtual GranaIterator<tip> dajSljedecuGranu(int p, int d) = 0;
};

template <typename tip> class Cvor {

  UsmjereniGraf<tip> *u;
  tip oznaka;
  int broj;
  std::vector<Grana<tip>> grane;
  std::vector<Cvor<tip>> susjedi;

public:
  Cvor(UsmjereniGraf<tip> *a, int b) : u(a), broj(b) {}

  int dajRedniBroj() const { return broj; }

  void postaviOznaku(tip a) { u->postaviOznakuCvora(broj, a); }

  tip dajOznaku() const { return u->dajOznakuCvora(broj); }

  void dodajVezu(Grana<tip> g, Cvor<tip> s) {
    grane.push_back(g);
    susjedi.push_back(s);
  }
  void obrisiVezu(Grana<tip> g, Cvor<tip> s) {

    for (int i = 0; i < susjedi.size(); i++)
      if (s == susjedi[i]) {

        for (int j = i; j < susjedi.size() - 1; j++) {
          susjedi[j] = susjedi[j + 1];
          grane[j] = grane[j + 1];
        }
        break;
      }
    susjedi.pop_back();
    grane.pop_back();
  }

  std::vector<Grana<tip>> dajGrane() const { return grane; }
  std::vector<Cvor<tip>> dajSusjede() const { return susjedi; }
};

template <typename tip> class Grana {

  UsmjereniGraf<tip> *u;
  tip oznaka;
  float tezina;
  int p, d;

public:
  Grana(UsmjereniGraf<tip> *ug, int polazni, int dolazni)
      : u(ug), p(polazni), d(dolazni) {}
  float dajTezinu() const { return u->dajTezinuGrane(p, d); }
  void postaviTezinu(float a) { u->postaviTezinuGrane(p, d, a); }
  void postaviOznaku(tip a) { u->postaviOznakuGrane(p, d, a); }
  tip dajOznaku() const { return u->dajOznakuGrane(p, d); }
  Cvor<tip> dajPolazniCvor() const { return u->dajCvor(p); };
  Cvor<tip> dajDolazniCvor() const { return u->dajCvor(d); };
};

template <typename tip> class GranaIterator {

  int p, d;
  UsmjereniGraf<tip> *u;

public:
  GranaIterator(UsmjereniGraf<tip> *us, int a, int b) : p(a), d(b), u(us){};

  Grana<tip> operator*() { return u->dajGranu(p, d); }
  bool operator==(const GranaIterator &it) const {
    return it.u == u && it.p == p && it.d == d;
  }
  bool operator!=(const GranaIterator &it) const {
    return it.u != u || it.p != p || it.d != d;
  }
  GranaIterator &operator++() {
    GranaIterator<tip> sljedeci = u->dajSljedecuGranu(p, d);
    p = sljedeci.p;
    d = sljedeci.d;
    return *this;
  }
  GranaIterator operator++(int) {
    GranaIterator<tip> ovaj = *this;
    ++(*this);
    return ovaj;
  }
};

template <typename tip> class ListaGraf : public UsmjereniGraf<tip> {

  struct grana {
    tip oznaka;
    float tezina;
    bool postoji;
  };
  std::vector<std::vector<grana>> lista;
  std::vector<tip> oznake;

public:
  ListaGraf(int b) : UsmjereniGraf<tip>(b) { postaviBrojCvorova(b); }
  int dajBrojCvorova() const override { return lista.size(); }

  void postaviBrojCvorova(int a) override {
    grana g;
    g.postoji = false;
    for (int i = 0; i < lista.size(); i++)
      lista[i].resize(a, g);
    std::vector<grana> ubaci(a, g);
    lista.resize(a, ubaci);
    oznake.resize(a);
  }
  bool postojiGrana(int p, int d) override { return lista[p][d].postoji; }

  void dodajGranu(int p, int d, float t) override {
    grana g;
    g.tezina = t;
    g.postoji = true;
    lista[p][d] = g;
  }
  void obrisiGranu(int p, int d) override { lista[p][d].postoji = false; }
  void postaviTezinuGrane(int p, int d, float t) override {
    lista[p][d].tezina = t;
  }
  tip dajOznakuCvora(int b) override { return oznake[b]; }

  tip dajOznakuGrane(int p, int d) override { return lista[p][d].oznaka; }
  float dajTezinuGrane(int p, int d) override { return lista[p][d].tezina; }
  void postaviOznakuCvora(int b, tip a) override { oznake[b] = a; }
  void postaviOznakuGrane(int p, int d, tip a) override {
    lista[p][d].oznaka = a;
  }
  GranaIterator<tip> dajGranePocetak() {
    GranaIterator<tip> it(this, 0, -1);
    ++it;
    return it;
  }
  GranaIterator<tip> dajGraneKraj() {
    GranaIterator<tip> it(this, -1, -1);
    return it;
  }

  GranaIterator<tip> dajSljedecuGranu(int p, int d) override {
    for (int i = p; i < lista.size(); i++) {
      for (int j = 0; j < lista.size(); j++) {
        if (i == p && j <= d)
          continue;

        if (lista[i][j].postoji)
          return GranaIterator<tip>(this, i, j);
      }
    }
    return GranaIterator<tip>(this, -1, -1);
  }
};

template <typename tip>
void bfs(UsmjereniGraf<tip> *g, std::vector<Cvor<tip>> &b, Cvor<tip> c) {
  bool dodati = false;
  for (int i = 0; i < b.size(); i++) {
    if (b[i].dajRedniBroj() == c.dajRedniBroj()) {
      dodati = true;
      break;
    }
  }
  if (!dodati)
    b.push_back(c);
  int br = g->dajBrojCvorova();
  for (int i = 0; i < br; i++)
    if (!dodati)
      bfs(g, b, g->dajCvor(i));
}

template <typename tip>
void dfs(UsmjereniGraf<tip> *g, std::vector<Cvor<tip>> &b, Cvor<tip> c) {
  bool dodati = false;
  for (int i = 0; i < b.size(); i++) {
    if (c.dajRedniBroj() == b[i].dajRedniBroj()) {
      dodati = true;
      break;
    }
  }
  if (!dodati)
    b.push_back(c);
  int brojCvorova = g->dajBrojCvorova();
  for (int i = 0; i < brojCvorova; i++)
    if (g->postojiGrana(c.dajRedniBroj(), i) && !dodati)
      dfs(g, b, g->dajCvor(i));
}

int main() {
  HashMapaLan<std::string, std::string> m;
  // Nije definisana hash funkcija!
  std::string s1("Sarajevo"), s2("Zagreb");
  m[s1] = "BiH";
  m[s2] = "Hrvatska";
  std::cout << m.brojElemenata() << " " << m[s2];
  return 0;
}