#include <iostream>
#include <stdexcept>

using namespace std;

template <typename tip> class Lista
{
    public:
    Lista(){;}
    virtual ~Lista(){}
    virtual int brojElemenata() const=0;
    virtual tip &trenutni()=0;
    virtual tip trenutni() const=0;
    virtual bool sljedeci()=0;
    virtual bool prethodni()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual tip &operator[](int i)=0;
    virtual const tip operator[](int i) const=0;
    virtual void dodajIspred(const tip &x)=0;
    virtual void dodajIza(const tip &x)=0;
};

template <typename tip>
struct Cvor
{
    tip x;
    Cvor* sljedeci;
    Cvor* prethodni;
};

template <typename tip> class DvostrukaLista : public Lista<tip>
{
    private:
    Cvor<tip>* prvi;
    Cvor<tip>* tekuci;
    Cvor<tip>* posljednji;
    int el;

    public:
    DvostrukaLista<tip>():prvi(nullptr),tekuci(nullptr),posljednji(nullptr),el(0)
    {;}
    ~DvostrukaLista<tip>()
    {
        while(prvi!=nullptr)
        {
            tekuci=prvi;
            prvi=prvi->sljedeci;
            delete tekuci;
        }
        el=0;
    }
    int brojElemenata() const {return el;}
    DvostrukaLista<tip>(const DvostrukaLista<tip> &x)
    {
        el=0;
        prvi=nullptr;
        tekuci=nullptr;
        posljednji=nullptr;
        if(x.el==0)
        {
            prvi=nullptr;
            tekuci=nullptr;
            posljednji = nullptr;
        }
        else {
            Cvor<tip>* temp(x.prvi);
            if(prvi)
            pocetak();
            while(temp!=nullptr)
            {
                dodajIza(temp->x);
                sljedeci();
                temp=temp->sljedeci;
                posljednji=tekuci;
            }
        }
    }

    tip &trenutni()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        return tekuci->x;
    }
    tip trenutni() const
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        return tekuci->x;
    }
    bool prethodni()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        if(tekuci==prvi)
        return false;
        tekuci=tekuci->prethodni;
        return true;
    }
    bool sljedeci()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        if(tekuci->sljedeci==nullptr)
        return false;
        tekuci=tekuci->sljedeci;
        return true;
    }
    void pocetak()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        tekuci=prvi;
    }
    void kraj()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        tekuci=posljednji;
    }
    void obrisi()
    {
        if(prvi==nullptr)
            throw std::range_error("Nema elemenata");
        if(tekuci==prvi)
        {
            prvi=prvi->sljedeci;
            delete tekuci;
            tekuci=prvi;
            el--;
            if(el==0)
            posljednji=nullptr;
        }
        else
        {
            Cvor<tip>* temp(prvi);
            while(temp->sljedeci!=tekuci)
                temp=temp->sljedeci;

            temp->sljedeci=tekuci->sljedeci;
            delete tekuci;

            if(temp->sljedeci==nullptr)
                posljednji=tekuci=temp;
            else
            {
                temp->sljedeci->prethodni=temp;
                tekuci=temp->sljedeci;
            }
            el--;
        }
    }
    DvostrukaLista<tip> &operator=(const DvostrukaLista<tip> &x)
    {
        if(this==&x)
            return *this;
        while(prvi!=nullptr)
        {
            tekuci=prvi;
            prvi=prvi->sljedeci;
            delete tekuci;
        }
        el=0;
        if(x.el==0)
        {
            prvi=nullptr;
            tekuci=nullptr;
            posljednji=nullptr;
        }
        else
        {
            Cvor<tip>* temp(x.prvi);
            while(temp!=nullptr)
            {
                dodajIza(temp->x);
                sljedeci();
                temp=temp->sljedeci;
                posljednji=tekuci;
            }
        }
        return *this;
    }
    tip &operator[](int i)
    {
        if(i<0 || i>=el)
            throw std::range_error("Nema elemenata");
        Cvor<tip>* temp(prvi);
        for(int j=0;j<i;j++)
            temp=temp->sljedeci;
        return temp->x;
    }

    const tip operator[](int i) const
    {
        if(i<0 || i>=el)
            throw std::range_error("Nema elemenata");
        Cvor<tip>* temp(prvi);
        for(int j=0;j<i;j++)
            temp=temp->sljedeci;
        return temp->x;
    }

    void dodajIspred(const tip &x)
    {
        Cvor<tip>* novi = new Cvor<tip>();
        novi->x=x;
        if(prvi==nullptr)
        {
            prvi=posljednji=tekuci=novi;
            prvi->sljedeci=nullptr;
            tekuci->sljedeci=nullptr;
        }
        else if(prvi==tekuci)
        {
        novi->sljedeci=prvi;
        prvi->prethodni=novi;
        prvi=novi;
        }
        else
        {
            novi->prethodni=tekuci->prethodni;
            tekuci->prethodni=novi;
            novi->sljedeci=tekuci;
            novi->prethodni->sljedeci=novi;
        }
        el++;
    }

    void dodajIza(const tip &x)
    {
        Cvor<tip>* novi=new Cvor<tip>();
        novi->x=x;
        if(prvi==nullptr)
        {
            prvi=posljednji=tekuci=novi;
            prvi->sljedeci=nullptr;
            novi->sljedeci=nullptr;
            tekuci->sljedeci=nullptr;
        }
        else
        {
            novi->sljedeci=tekuci->sljedeci;
            novi->prethodni=tekuci;
            tekuci->sljedeci=novi;
            if(tekuci==posljednji)
                posljednji=novi;
            else
            {
            novi->sljedeci->prethodni=novi;
            }
        }
        el++;
    }
    template <typename tipp>
    friend class Iter;
};

template <typename tipp>
class Iter
{
    const DvostrukaLista<tipp>* lista;
    Cvor<tipp>* trenutno;
    public:
    Iter(const DvostrukaLista<tipp> &l)
    {
        lista=&l;
        trenutno=l.prvi;
    }
    tipp dajTrenutni()
    {
        if(!lista->brojElemenata())
            throw std::domain_error("lista prazna");
        return trenutno->x;
    }
    bool sljedeci()
    {
        if(!lista->brojElemenata())
            throw std::domain_error("Lista prazna");
        if(!trenutno->sljedeci)
            return false;
        trenutno=trenutno->sljedeci;
            return true;
    }

};
template<typename tip>
tip dajMaksimum(const Lista<tip> &b)
{
    if(b.brojElemenata()==0)
        throw std::range_error("Nema elemenata");
    Iter<tip> it=dynamic_cast<const DvostrukaLista<tip>&>(b);
    tip max=it.dajTrenutni();
    while(it.sljedeci())
    if(it.dajTrenutni()>max)
        max=it.dajTrenutni();
    return max;
};

int main()
{

}