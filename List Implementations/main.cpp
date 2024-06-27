#include <iostream>
#include <list>
#include <stdexcept>

template <typename tip> class Lista {
public:
  Lista() { ; }
  virtual ~Lista() { ; }
  virtual int brojElemenata() const = 0;
  virtual tip &trenutni() = 0;
  virtual tip trenutni() const = 0;
  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  virtual void dodajIspred(const tip &x) = 0;
  virtual void dodajIza(const tip &x) = 0;
  virtual tip &operator[](int x) = 0;
  virtual const tip operator[](int x) const = 0;
};

template <typename tip> class NizLista : public Lista<tip> {
protected:
  tip *pok;
  int vel, el, tekuci, elL, elD;

public:
  NizLista<tip>()
      : Lista<tip>(), vel(10000), el(0), tekuci(0), elL(0), elD(0),
        pok(nullptr) {
    ;
  }
  NizLista<tip>(const NizLista<tip> &niz) {
    el = niz.el;
    elL = niz.elL;
    elD = niz.elD;
    vel = niz.vel;
    if (niz.el == 0)
      pok = nullptr;
    else {
      pok = new tip[niz.vel];
      for (int i = vel / 2 - elL + 1; i < vel / 2 + elD; i++)
        pok[i] = niz.pok[i];
    }
    tekuci = niz.tekuci;
  }
  ~NizLista() { delete[] pok; }
  int brojElemenata() const { return el; }
  int brojLElemenata() const { return elL; }
  int brojDElemenata() const { return elD; }
  int velicina() const { return vel; }

  NizLista<tip> &operator=(const NizLista<tip> &niz) {
    if (this == &niz)
      return *this;

    el = niz.el;
    elL = niz.elL;
    elD = niz.elD;
    vel = niz.vel;
    if (niz.el == 0)
      pok = nullptr;
    else {
      pok = new tip[niz.vel];
      for (int i = vel / 2 - elL + 1; i < vel / 2 + elD; i++)
        pok[i] = niz.pok[i];
    }
    tekuci = niz.tekuci;
    return *this;
  }

  void obrisi() {
    if (vel / 2 - elL > tekuci || vel / 2 + elD < tekuci)
      throw std::range_error("Nema elemenata");
    if (elD != 0) {
      for (int i = tekuci; i < vel / 2 + elD; i++)
        pok[i] = pok[i + 1];
      elD--;
    } else if (elL != 0) {
      for (int i = tekuci; i > vel / 2 + elL; i--)
        pok[i] = pok[i - 1];
      elL--;
    }
    el--;
  }
  tip trenutni() const {
    if (vel / 2 - elL > tekuci || vel / 2 + elD < tekuci || el == 0)
      throw std::range_error("Nema elemenata");

    return pok[tekuci];
  }
  tip &trenutni() {
    if (vel / 2 - elL > tekuci || vel / 2 + elD < tekuci || el == 0)
      throw std::range_error("Nema elemenata");

    return pok[tekuci];
  }
  bool prethodni() {
    if (vel / 2 - elL - 1 >= tekuci)
      throw std::range_error("Nema elemenata");
    if (tekuci == vel / 2 - elL)
      return false;
    tekuci--;
    return true;
  }
  bool sljedeci() {
    if (vel / 2 + elD + 1 <= tekuci)
      throw std::range_error("Nema elemenata");
    if (tekuci == vel / 2 + elD)
      return false;
    tekuci++;
    return true;
  }
  void pocetak() {
    if (vel / 2 - elL > tekuci || vel / 2 + elD < tekuci || el == 0)
      throw std::range_error("Nema elemenata");
    tekuci = vel / 2 - elL;
  }
  void kraj() {
    if (vel / 2 - elL > tekuci || vel / 2 + elD < tekuci || el == 0)
      throw std::range_error("Nema elemenata");
    tekuci = vel / 2 + elD;
  }

  tip &operator[](int i) {
    if (i < 0 || i > el - 1)
      throw std::range_error("Nema elemenata");
    return pok[vel / 2 - elL + i];
  }

  const tip operator[](int i) const {
    if (i < 0 || i > el - 1)
      throw std::range_error("Nema elemenata");
    return pok[vel / 2 - elL + i];
  }

  void dodajIza(const tip &niz) {
    if (el == 0) {
      delete[] pok;
      vel = 20001;
      el++;
      pok = new tip[20001];
      pok[vel / 2] = niz;
      tekuci = vel / 2;
    } else {
      if (vel / 2 == elD) {
        auto temp = new tip[vel];
        for (int i = 0; i < elL; i++)
          temp[vel / 2 - i] = pok[vel / 2 - i];
        for (int i = 1; i < elD; i++)
          temp[vel / 2 + i] = pok[vel / 2 + i];

        delete[] pok;
        pok = new tip[vel + 20000];

        for (int i = 0; i < elL; i++)
          pok[vel / 2 - i] = temp[vel / 2 - i];
        for (int i = 1; i < elD; i++)
          pok[vel / 2 + i] = temp[vel / 2 + i];

        vel = vel + 20000;
        delete[] temp;
      }

      for (int i = vel / 2 + elD + 1; i > tekuci; i--)
        pok[i] = pok[i - 1];
      pok[tekuci + 1] = niz;
      elD++;
      el++;
    }
  }

  void dodajIspred(const tip &niz) {
    if (el == 0) {
      delete[] pok;
      vel = 20001;
      el++;
      pok = new tip[20001];
      pok[vel / 2] = niz;
      tekuci = vel / 2;
    } else {

      if (vel / 2 == elL) {
        auto temp = new tip[vel];
        for (int i = 0; i < elL; i++)
          temp[vel / 2 - i] = pok[vel / 2 - i];
        for (int i = 1; i < elD; i++)
          temp[vel / 2 + i] = pok[vel / 2 + i];

        delete[] pok;
        pok = new tip[vel + 20000];

        for (int i = 0; i < elL; i++)
          pok[vel / 2 - i] = temp[vel / 2 - i];
        for (int i = 1; i < elD; i++)
          pok[vel / 2 + i] = temp[vel / 2 + i];

        vel = vel + 20000;
        delete[] temp;
      }
      for (int i = vel / 2 - elL - 1; i < tekuci; i++)
        pok[i] = pok[i + 1];
      pok[tekuci - 1] = niz;
      el++;
      elL++;
    }
  }
};

template <typename tip> class JednostrukaLista : public Lista<tip> {
private:
  struct Cvor {
    tip x;
    Cvor *sljedeci;
  };
  Cvor *prvi, *posljednji, *tekuci;
  int el;

public:
  JednostrukaLista<tip>()
      : prvi(nullptr), posljednji(nullptr), tekuci(nullptr), el(0) {
    ;
  }
  ~JednostrukaLista() {
    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->sljedeci;
      delete tekuci;
    }
    el = 0;
  }
  int brojElemenata() const { return el; }

  tip &trenutni() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    return tekuci->x;
  }
  tip trenutni() const {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    return tekuci->x;
  }
  void pocetak() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    tekuci = prvi;
  }
  void kraj() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    tekuci = posljednji;
  }
  bool prethodni() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    if (tekuci == prvi)
      return false;

    Cvor *temp(prvi);
    while (temp->sljedeci != tekuci)
      temp = temp->sljedeci;

    tekuci = temp;
    return true;
  }
  bool sljedeci() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    if (tekuci->sljedeci == nullptr)
      return false;

    tekuci = tekuci->sljedeci;
    return true;
  }
  void obrisi() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    if (tekuci == prvi) {
      prvi = prvi->sljedeci;
      delete tekuci;
      tekuci = prvi;
      el--;
      if (el == 0)
        posljednji = nullptr;
    } else {
      Cvor *temp(prvi);
      while (temp->sljedeci != tekuci)
        temp = temp->sljedeci;
      temp->sljedeci = tekuci->sljedeci;
      delete tekuci;
      tekuci = temp->sljedeci;

      if (tekuci == nullptr)
        posljednji = tekuci = temp;

      el--;
    }
  }
  JednostrukaLista(const JednostrukaLista<tip> &x) {
    el = 0;
    prvi = nullptr;
    tekuci = nullptr;
    posljednji = nullptr;

    if (x.el == 0) {
      prvi = nullptr;
      posljednji = nullptr;
      tekuci = nullptr;
    } else {
      Cvor *temp(x.prvi);
      if (prvi)
        pocetak();

      while (temp != nullptr) {
        dodajIza(temp->x);
        sljedeci();
        temp = temp->sljedeci;

        posljednji = tekuci;
      }
    }
  }
  JednostrukaLista<tip> &operator=(const JednostrukaLista<tip> &x) {
    if (this == &x)
      return *this;
    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->sljedeci;
      delete tekuci;
    }
    el = 0;
    if (x.el == 0) {
      prvi = nullptr;
      posljednji = nullptr;
      tekuci = nullptr;
    } else {
      Cvor *temp(x.prvi);
      while (temp != nullptr) {
        dodajIza(temp->x);
        sljedeci();
        temp = temp->sljedeci;
        posljednji = tekuci;
      }
    }
    return *this;
  }

  tip &operator[](int i) {
    if (i < 0 || i >= el)
      throw std::range_error("Nema elemenata");
    Cvor *temp(prvi);
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->x;
  }

  const tip operator[](int i) const {
    if (i < 0 || i >= el)
      throw std::range_error("Nema elemenata");
    Cvor *temp(prvi);
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->x;
  }

  void dodajIspred(const tip &x) {
    Cvor *novi = new Cvor;
    novi->x = x;
    if (prvi == nullptr) {
      prvi = posljednji = tekuci = novi;
      prvi->sljedeci = nullptr;
      tekuci->sljedeci = nullptr;
    } else if (prvi == tekuci) {
      novi->sljedeci = prvi;
      prvi = novi;
    } else {
      Cvor *temp = prvi;
      while (temp->sljedeci != tekuci)
        temp = temp->sljedeci;
      temp->sljedeci = novi;
      novi->sljedeci = tekuci;
    }
    el++;
  }

  void dodajIza(const tip &x) {
    Cvor *novi = new Cvor;
    novi->x = x;
    if (prvi == nullptr) {
      prvi = posljednji = tekuci = novi;
      prvi->sljedeci = nullptr;
      novi->sljedeci = nullptr;
      tekuci->sljedeci = nullptr;
    } else {
      novi->sljedeci = tekuci->sljedeci;
      tekuci->sljedeci = novi;
      if (tekuci == posljednji)
        posljednji = novi;
    }
    el++;
  }
};

int main() {
  NizLista<int> niz;
  for (int i(1); i <= 5; i++)
    niz.dodajIspred(i);
  {
    NizLista<int> niz2(niz);
    NizLista<int> niz3;
    niz3 = niz;
    niz.obrisi();
    std::cout << niz2.brojElemenata();
    std::cout << " " << niz3.brojElemenata() << " ";
  }
  std::cout << niz.brojElemenata();
}