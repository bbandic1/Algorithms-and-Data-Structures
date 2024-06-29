#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename tip>
class Grana;

template <typename tip>
class Cvor;

template <typename tip>
class GranaIterator;

template <typename tip>
class UsmjereniGraf {

public:
    UsmjereniGraf(int p) {}
    virtual ~UsmjereniGraf() {}
    virtual void postaviBrojCvorova(int) = 0;
    virtual void postaviTezinuGrane(int, int, double) = 0;
    virtual void postaviOznakuCvora(int, tip) = 0;
    virtual void postaviOznakuGrane(int, int, tip) = 0;
    virtual void dodajGranu(int, int, double) = 0;
    virtual void obrisiGranu(int, int) = 0;
    virtual int dajBrojCvorova() const = 0;
    virtual double dajTezinuGrane(int, int)  = 0;
    virtual tip dajOznakuCvora(int)  = 0;
    virtual tip dajOznakuGrane(int, int)  = 0;
    virtual Grana<tip> &dajGranu(int, int) = 0;
    virtual Cvor<tip> &dajCvor(int) = 0;
    virtual GranaIterator<tip> dajGranePocetak() = 0;
    virtual GranaIterator<tip> dajGraneKraj() = 0;
    virtual bool postojiGrana(int, int) = 0;
};

template <typename tip>
class Grana {
    int pocetak, kraj;
    double tezina;
    tip oznaka;
    UsmjereniGraf<tip> *usmjereniGraf;
public:
    Grana(int p, int k, UsmjereniGraf<tip> *g, double t) : pocetak(p), kraj(k), usmjereniGraf(g), tezina(t) {}

    tip dajOznaku() const {
        return oznaka;
    }
    double dajTezinu() const {
        return tezina;
    }
    Cvor<tip> dajPolazniCvor() {
       return usmjereniGraf -> dajCvor(pocetak);
    }
    Cvor<tip> dajDolazniCvor() {
        return usmjereniGraf -> dajCvor(kraj);
    }

    void postaviOznaku(tip o) {
        oznaka = o;
        usmjereniGraf -> dajGranu(pocetak, kraj).oznaka = o;
    }
    void postaviTezinu(double t) {
        tezina = t;
        usmjereniGraf -> dajGranu(pocetak, kraj).tezina = t;
    } 
};

template <typename tip>
class Cvor {
    int redniBroj;
    tip oznaka;
    UsmjereniGraf<tip> *usmjereniGraf;

public:
    Cvor(UsmjereniGraf<tip> *ug, int rb) : usmjereniGraf(ug), redniBroj(rb) {}

    int dajRedniBroj() const {
        return redniBroj;
    }
    tip dajOznaku() const {
        return oznaka;
    }

    void postaviOznaku(tip o) {
        oznaka = o;
    }
};

template <typename tip>
class GranaIterator {

    int dolazniCvor, polazniCvor, pozicija;
    std::vector<Grana<tip>> grane;
    std::vector<std::vector<bool>> vrijednosti;

    void trazi(int &brojac, int &red, int &kolona, bool uslov)  {
        for(int i = 0; i < vrijednosti.size(); i++) {
            for(int j = 0; j < vrijednosti[i].size(); j++) {
                if(brojac <= pozicija && vrijednosti[i][j]) {
                    brojac++;
                    red = i;
                    kolona = j;
                }
                else if(brojac > pozicija) {
                    uslov = true;
                    break;
                }
            }
            if(uslov)
                break;
        }
    }
public:
    GranaIterator(std::vector<std::vector<bool>> v, std::vector<Grana<tip>> g, int p, int k, int poz) {
        dolazniCvor = k;
        polazniCvor = p;
        pozicija = poz;
        grane = g;
        vrijednosti = v;
    }
   
    bool operator !=(GranaIterator it) {
        int brojac = 0, red = 0, kolona = 0;

        trazi(brojac, red, kolona, false);

        if(vrijednosti[red][kolona] != it.vrijednosti[red][kolona])
            return false;
        if(pozicija == grane.size())
            return false;
        return true;
    }
    bool operator !=(const GranaIterator &it) const {
        int brojac = 0, red = 0, kolona = 0;

        trazi(brojac, red, kolona, false);

        if(vrijednosti[red][kolona] != it.vrijednosti[red][kolona])
            return false;
        if(pozicija == grane.size())
            return false;
        return true;
    }
    GranaIterator &operator ++() {
        pozicija++;
        return *this;
    }
    GranaIterator operator ++(int) {
        GranaIterator temp = *this;
        ++*this;
        return temp;
    }

     Grana<tip> operator *() {
        int brojac = 0, red = 0, kolona = 0;

        trazi(brojac, red, kolona, false);

        for(int i = 0; i < grane.size(); i++) {
            if(grane[i].dajPolazniCvor().dajRedniBroj() == red && grane[i].dajDolazniCvor().dajRedniBroj() == kolona)
                return grane[i];
        }

        throw std::logic_error("Trazena grana ne postoji");
    }
    bool operator ==(const GranaIterator &it) const {
        int brojac = 0, red = 0, kolona = 0;

        trazi(brojac, red, kolona, false);

        if(vrijednosti[red][kolona] == it.vrijednosti[red][kolona])
            return true;
        return false;
    }
};

template <typename tip>
class MatricaGraf : public UsmjereniGraf<tip> {
    std::vector<Grana<tip>> grane;
    std::vector<Cvor<tip>> cvorovi;
    std::vector<std::vector<bool>> vrijednosti;
    public:
    MatricaGraf(int bc) : UsmjereniGraf<tip>(bc) {
        if(bc < 0)
            throw std::logic_error("Broj cvorova ne smije biti negativan!");
        
        vrijednosti.resize(bc);

        for(int i = 0; i < bc; i++) {
            vrijednosti[i].resize(bc);
            
            cvorovi.push_back(Cvor<tip>(this, i));

            for(int j = 0; j < bc; j++)
                vrijednosti[i][j] = false;
        }
    }
    ~MatricaGraf() {}
    MatricaGraf(const MatricaGraf<tip> &mg) {
        grane = mg.grane;
        cvorovi = mg.cvorovi;
        vrijednosti = mg.vrijednosti;
    }
    MatricaGraf<tip> &operator =(const MatricaGraf<tip> &mg) {
        if(&mg != this) {
            grane = mg.grane;
            cvorovi = mg.cvorovi;
            vrijednosti = mg.vrijednosti;    
        }
        return *this;
    }
        void dodajGranu(int p, int k, double t = 0) override {
        if(!postojiGrana(p, k)) {
            vrijednosti[p][k] = true;
            grane.push_back(Grana<tip>(p, k, this, t));
        }
        else
            throw std::logic_error("Grana vec postoji!");
    }
        Grana<tip> &dajGranu(int p, int k) override {
        for(int i = 0; i < grane.size(); i++) {
            if(grane[i].dajPolazniCvor().dajRedniBroj() == p && grane[i].dajDolazniCvor().dajRedniBroj() == k)
                return grane[i];
        }
        throw std::logic_error("Trazena grana ne postoji!");
    }
    Cvor<tip> &dajCvor(int i) override {
        return cvorovi[i];
    }
    GranaIterator<tip> dajGranePocetak() override {
        return GranaIterator<tip>(vrijednosti, grane, grane[0].dajPolazniCvor().dajRedniBroj(), grane[0].dajDolazniCvor().dajRedniBroj(), 0);
    }
    GranaIterator<tip> dajGraneKraj() override {
        return GranaIterator<tip>(vrijednosti, grane, grane[grane.size() - 1].dajPolazniCvor().dajRedniBroj(), grane[grane.size() - 1].dajDolazniCvor().dajRedniBroj(), 0);
    }

    bool postojiGrana(int p, int k) override {
        return vrijednosti[p][k];
    }
    void obrisiGranu(int p, int k) override {
        for(int i = 0; i < grane.size(); i++) {
            if(grane[i].dajPolazniCvor().dajRedniBroj() == p && grane[i].dajDolazniCvor().dajRedniBroj() == k) {
                vrijednosti[p][k] = false;
                grane.erase(grane.begin() + i);
                return;
            }
        }

        throw std::logic_error("Granu koju zelite obrisati ne postoji!");
    }
    void postaviBrojCvorova(int bc) override {
        if(bc < cvorovi.size()) 
            throw std::logic_error("Ne smije broj cvorova biti manji od prethodnog");
        
        if(vrijednosti.size() == bc)
            return;

        for(int i = vrijednosti.size(); i < bc; i++)
            cvorovi.push_back(Cvor<tip>(this, i));
        
        int staraDimenzijaMatrice = vrijednosti.size();

        vrijednosti.resize(bc);

        int ubaci = 0;
        for(int i = 0; i < bc; i++) {
            vrijednosti[i].resize(bc);
            
            if(i >= staraDimenzijaMatrice)
                ubaci = 0;
            else
                ubaci = staraDimenzijaMatrice;
            
            for(int j = ubaci; j < bc; j++)
                vrijednosti[i][j] = false;
        }
    }
    void postaviTezinuGrane(int p, int k, double t) override {
        for(int i = 0; i < grane.size(); i++) {
            if(p == grane[i].dajPolazniCvor().dajRedniBroj() && k == grane[i].dajDolazniCvor().dajRedniBroj()) {
                grane[i].postaviTezinu(t);
                return;
            }
        }
        throw std::logic_error("Ne mozete postaviti tezinu jer data grana ne postoji!");
    }
    void postaviOznakuCvora(int rb, tip o) override {
        cvorovi[rb].postaviOznaku(o);
    }
    void postaviOznakuGrane(int p, int k, tip o) override {
        for(int i = 0; i < grane.size(); i++) {
            if(p == grane[i].dajPolazniCvor().dajRedniBroj() && k == grane[i].dajDolazniCvor().dajRedniBroj()) {
                grane[i].postaviOznaku(o);
                return;
            }
        }
        throw std::domain_error("Ne mozete postaviti oznaku jer data grana ne postoji!");
    }


    int dajBrojCvorova() const override {
        return cvorovi.size();
    }
    double dajTezinuGrane(int p, int k)  override {
        for(int i = 0; i < grane.size(); i++) {
            if(p == grane[i].dajPolazniCvor().dajRedniBroj() && k == grane[i].dajDolazniCvor().dajRedniBroj()) {
                return grane[i].dajTezinu();
            }
        }
        throw std::logic_error("Trazena grana ne postoji!");
    }
    tip dajOznakuCvora(int rb)  override {
        return cvorovi[rb].dajOznaku();
        throw std::logic_error("Trazeni cvor ne postoji!");
    }
    tip dajOznakuGrane(int p, int k)  override {
        for(int i = 0; i < grane.size(); i++) {
            if(p == grane[i].dajPolazniCvor().dajRedniBroj() && k == grane[i].dajDolazniCvor().dajRedniBroj()) {
                return grane[i].dajOznaku();
            }
        }

        throw std::logic_error("Trazena grana ne postoji!");
    }
};

int main() {
UsmjereniGraf<bool> *g = new MatricaGraf<bool>(4);
  g->dodajGranu(0, 1, 2.5);
  g->dodajGranu(1, 2, 1.2);
  g->dodajGranu(1, 3, 0.1);
  g->dodajGranu(3, 3, -4.0);
  g->postaviTezinuGrane(1, 2, 0.2);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (g->postojiGrana(i,j))
        cout << "(" << i << "," << j << ") -> " << g->dajTezinuGrane(i, j) << "; ";
  delete g;
  return 0;
}
