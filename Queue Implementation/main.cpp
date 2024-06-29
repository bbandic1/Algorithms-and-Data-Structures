#include <iostream>
#include <stdexcept>

using namespace std;

template <typename tip> class Red{
    private:
    struct Cvor
    {
        tip x;
        Cvor* sljedeci;
    };
    Cvor* poc;
    Cvor* kraj;
    int el;
    
    public:
    Red<tip>(): poc(nullptr),el(0),kraj(nullptr){}
    ~Red()
    {
        kraj=nullptr;
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci;
            delete tekuci;
        }
        el=0;
    }
    int brojElemenata() const {return el;}

    Red(const Red<tip> &x)
    {
        el=0;
        poc=nullptr;
        if(x.el==0)
        {
            poc=nullptr;
            kraj=nullptr;
        }
        else{
            Cvor* temp(x.poc);
            while(temp!=nullptr)
            {
                stavi(temp->x);
                temp=temp->sljedeci;
            }
        }
    }
    Red<tip> &operator=(const Red<tip> &x)
    {
        if(this==&x)
        return *this;

        while(poc!=kraj)
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
            
        return *this;
        }
    }
    void stavi(const tip &x)
    {
        Cvor* novi=new Cvor;
        novi->x=x;

        if(poc==nullptr)
        {
            poc=novi;
            kraj=novi;
            poc->sljedeci=nullptr;
            kraj->sljedeci=nullptr;
        }
        else
        {
            kraj->sljedeci=novi;
            kraj=novi;
            kraj->sljedeci=nullptr;
        }
        el++;
    }
    tip skini()
    {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
        tip b=poc->x;
        if(el==1)
        kraj=nullptr;

        auto tekuci=poc;
        poc=poc->sljedeci;
        delete tekuci;
        el--;

        return b;
    }
    void brisi()
    {
        kraj=nullptr;
        while(poc!=nullptr)
        {
            auto tekuci=poc;
            poc=poc->sljedeci;
            delete tekuci;
        }
        el=0;
    }
    void ispisi() const {
        if(el<=0)
            throw std::range_error("Nema elemenata");
        auto tekuci=poc;
        while(tekuci!=kraj)
        {
            std::cout << tekuci->x;
            if(tekuci->sljedeci!=nullptr)
            std::cout << " ";
            tekuci=tekuci->sljedeci;
        }
    }
    tip &celo()
    {
        if(poc==nullptr)
            throw std::range_error("Nema elemenata");
        return poc->x;
    }
};
int main()
{

Red<int> r;
for (int i(1); i<=5; i++)
    r.stavi(i);
    try{
for (int i(0); i<=6;i++)
    r.skini();
    }
    catch(...){
        cout<<"Izuzetak";   
    }

}
