#include <iostream>
#include <stdexcept>
#include <list>

using namespace std;

template <typename tip> class DvostraniRed
{
    private:
    struct Cvor
    {
        tip x;
        Cvor* prethodni;
        Cvor* sljedeci;
    };

    Cvor* top;
    Cvor* poc;
    int el;

    public:
    DvostraniRed<tip>():top(nullptr),poc(nullptr),el(0){;}
    ~DvostraniRed()
    {
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci;
            delete tekuci;
        }
        el=0;
    }
    DvostraniRed(const DvostraniRed<tip> &x)
    {
        el=0;
        top=nullptr;
        
        if(x.el==0)
        {
            poc=top=nullptr;

        }
        else {
            Cvor* temp(x.poc);

            while(temp!=nullptr)
            {
                staviNaVrh(temp->x);
                temp=temp->sljedeci;
            }
        }
    }
    int brojElemenata() const {return el;}
    
    void brisi()
    {
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci; 
            delete tekuci;
        }
        el=0;
    }

    void staviNaVrh(const tip &x)
    {
        Cvor* novi=new Cvor;
        novi->x=x;
        if(el==0)
        {
            top=novi;
            poc=novi;
            top->prethodni=top->sljedeci=nullptr;
            poc->prethodni=poc->sljedeci=nullptr;
        }
        else {
            top->sljedeci=novi;
            novi->prethodni=top;
            top=novi;
            top->sljedeci=nullptr;
        }
        el++;
    }

    void staviNaCelo(const tip &x)
    {
        Cvor* novi=new Cvor;
        novi->x=x;
        if(poc==nullptr)
        {
            top=novi;
            poc=novi;
            top->prethodni=top->sljedeci=nullptr;
            poc->prethodni=poc->sljedeci=nullptr;
        }
        else {
            novi->sljedeci=poc;
            poc->prethodni=novi;
            poc=novi;
            poc->prethodni=nullptr;
        }
        el++;
    }
    
    tip skiniSaVrha()
    {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
        tip clan=top->x;
        if(el==1)
             poc=nullptr;
        auto tekuci=top;
        top=top->prethodni;
        delete tekuci;
         el--;
        return clan;
    }

    tip skiniSaCela()
    {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
         tip clan=poc->x;
        if(el==1)
            top=nullptr;
        auto tekuci=poc;
        poc=poc->sljedeci;
        delete tekuci;
        el--;
        return clan;
    }

    tip &vrh()
    {
        if(top==nullptr)
            throw std::range_error("Nema elemenata");
        return top->x;
    }

    tip &celo()
    {
        if(top==nullptr)
            throw std::range_error("Nema elemenata");
        return poc->x;
    }

    DvostraniRed<tip> &operator=(const DvostraniRed<tip> &x)
    {
        if(this==&x)
            return *this;
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci;
            delete tekuci;
        }
        el=0;
        if(x.el==0)
            poc=top=nullptr;
        else 
        {
            Cvor* temp(x.poc);
            while(temp!=nullptr)
            {
                staviNaVrh(temp->x);
                temp=temp->sljedeci;
            }
        }
        return *this;       
    }

    void ispisi() const
    {
        if(el<=0)
            throw std::range_error("Nema elemenata");
            auto tekuci=poc;
            while(tekuci!=top)
            {
                std::cout << tekuci->x;
                if(tekuci->sljedeci!=nullptr)
                    std::cout << " ";
                tekuci=tekuci->sljedeci;
            }
    }
    
};

int main()
{


}