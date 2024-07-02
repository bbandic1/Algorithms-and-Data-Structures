#include <iostream>
#include <stdexcept>
#include <list>
#include <vector>

using namespace std;

template<typename tip> class Stek
{
    private:
    struct Cvor
    {
        tip x;
        Cvor* sljedeci;
    };

    Cvor* top;
    int el;

    public:
    Stek<tip>() : top(nullptr),el(0){;}
    ~Stek()
    {
        while(top!=nullptr)
        {
            auto tekuci=top;
            top=top->sljedeci;
            delete tekuci;
        }
        el=0;
    }

    Stek(const Stek<tip> &x)
    {
        el=0;
        top=nullptr;

        if(x.el==0)
            top=nullptr;
        else
        {
            Cvor* temp(x.top);
            while(temp!=nullptr)
            {
                stavi(temp->x);
                temp=temp->sljedeci;
            }
            temp=x.top;
            Cvor* tekuci(top);
            while(temp!=nullptr)
            {
                tekuci->x=temp->x;
                temp=temp->sljedeci;
                tekuci=tekuci->sljedeci;
            }

        }
    }
    int brojElemenata() const {return el;}

    void brisi()
    {
        while(top!=nullptr)
        {
            auto tekuci=top;
            top=top->sljedeci;
            delete tekuci;
        }
        el=0;
    }

    void stavi(const tip &x) {
    Cvor* novi = new Cvor;
    novi->x = x;
    novi->sljedeci = top;
    top = novi;
    el++;
}

    tip skini()
    {
        if(top==nullptr)
            throw std::range_error("Nema elementa");

        tip clan = top->x;
        auto tekuci = top;
        top = top->sljedeci;
        delete tekuci;
        el--;
        return clan;
    }

    tip Vrh() const
    {
        if(top==nullptr)
            throw std::range_error("Nema elementa");
        return top->x;
    }

    tip &vrh()
    {
        if(top==nullptr)
            throw std::range_error("Nema elementa");
        return top->x;
    }

        Stek<tip> &operator=(const Stek<tip> &x)
    {
        if(this==&x)
            return *this;
        while(top!=nullptr)
        {
            auto tekuci = top;
            top=top->sljedeci;
            delete tekuci;
        }
        el=0;
        if(x.el==0)
            top=nullptr;
        else
        {
            Cvor* temp(x.top);
            while(temp!=nullptr)
            {
                stavi(temp->x);
                temp=temp->sljedeci;
            }
            temp=x.top;
            Cvor* tekuci(top);
            while(temp!=nullptr)
            {
                tekuci->x=temp->x;
                temp=temp->sljedeci;
                tekuci=tekuci->sljedeci;
            }
            return *this;
        }
    }

    void ispisi() const
    {
        if(el<=0)
            throw std::range_error("Nema elementa");
        auto tekuci=top;
        while(tekuci!=nullptr)
        {
            std::cout << tekuci->x;
            if(tekuci->sljedeci!=nullptr)
                std::cout << " ";
            tekuci=tekuci->sljedeci;
        }
    }
    
};
    void pretraga(Stek<std::vector<int>> &v, int trazeni)
    {
        int n=v.brojElemenata();
        static int i(0),a(-1),b(0),m(n);
        std::vector<int> pv{};
        if(v.brojElemenata()==0)
            goto start2;
        pv=v.skini();
        if(pv.size()!=0 && pv[0]>trazeni){;}
        else if(pv.size()!=0 && pv[pv.size()-1]<trazeni)
            goto start;
        else
        {
            int c=pv.size();
            for(int j(0);j<c;)
                {
                    int sredina=(j+c-1)/2;
                    if(trazeni==pv[sredina])
                        {
                            a=sredina;
                            b=i;
                            goto start;
                        }
                    else if(trazeni>pv[sredina])
                        j=sredina+1;
                    else 
                        c=sredina-1;
                }
        }

        start:
        if(v.brojElemenata()!=0 && a==-1)
            {
                i++;
                pretraga(v,trazeni);
            }
        v.stavi(pv);

        start2:
        if(v.brojElemenata()==m)
            {
                if(a==-1)
                    std::cout << "Nema elementa";
                else
                    std::cout << a << " " << n-b-1;
            }
    }

int main()
{
Stek<vector<int> > s;
vector<int> a;
for (int i(0); i<5; i++)
a.push_back(i);
vector<int> b;
vector<int> c;
vector<int> d;
for (int i(5); i<7; i++)
b.push_back(i);
s.stavi(a);
s.stavi(b);
c.push_back(8);
s.stavi(c);
d.push_back(9);
s.stavi(d);
pretraga(s,2);
cout<<" ";
while(s.brojElemenata()!=0){
    vector<int> k = s.skini();
    for(int i(0);i<k.size();i++){
        cout<<k[i]<<" ";
    }
}
}