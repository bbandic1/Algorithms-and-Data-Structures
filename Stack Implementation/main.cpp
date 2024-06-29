#include <iostream>
#include <stdexcept>
#include <list>

using namespace std;

template <typename tip> class Stek 
{
    private:

    struct Cvor {
        tip x;
        Cvor* sljedeci;
    };
    Cvor* poc;
    int el;

    public:
    Stek<tip>(): poc(nullptr),el(0) {;}
    ~Stek()
    {
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci;
            delete tekuci;
        }
        el=0;
    }
    int brojElemenata() const {return el;}
    Stek(const Stek<tip> &x)
    {
        el=0;
        poc=nullptr;
        if(x.el==0)
        {
            poc=nullptr;
        }
        else{
            Cvor* temp(x.poc);
            while(temp!=nullptr)
            {
                stavi(temp->x);
                temp=temp->sljedeci;
            }
            temp=x.poc;
            Cvor* tekuci(poc);
            while(temp!=nullptr)
            {
                tekuci->x=temp->x;
                temp=temp->sljedeci;
                tekuci=tekuci->sljedeci;
            }
        }
    }
    Stek<tip> &operator=(const Stek<tip> &x)
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
        poc=nullptr;

        else
        {
            Cvor* temp(x.poc);
            while(temp!=nullptr)
            {
                stavi(temp->x);
                temp=temp->sljedeci;
            }
            temp=x.poc;
            Cvor* tekuci(poc);
            while(temp!=nullptr)
            {
                tekuci->x=temp->x;
                temp=temp->sljedeci;
                tekuci=tekuci->sljedeci;
            }
            return *this;
        }
    }
    tip vrh() const {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
        return poc->x;
    }

    tip &vrh() {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
        return poc->x;
    }
    void stavi(const tip &x)
    {
        Cvor* novi=new Cvor;
        novi->x=x;
        if(poc==nullptr)
        {
            poc=novi;
            poc->sljedeci=nullptr;
        }
        else
        {
            novi->sljedeci=poc;
            poc=novi;
        }
        el++;
    }
    tip skini()
    {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");

        tip b=poc->x;

        auto tekuci=poc;
        poc=poc->sljedeci;
        delete tekuci;
        el--;

        return b; 
    }
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
    void ispisi() const
    {
        if(el<=0)
            throw std::range_error("Nema elemenata");
        
        auto tekuci=poc;
        while(tekuci!=nullptr)
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
    Stek<int> s;
for (int i(1); i<=5; i++)
	s.stavi(i);
	try{
for (int i(0); i<=6;i++)
    s.skini();
	}
	catch(...){
	    cout<<"Izuzetak";   
	}

}