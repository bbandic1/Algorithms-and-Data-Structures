#include <iostream>
#include <list>
#include <utility>
#include <cmath>

using namespace std;

template <typename tip1,typename tip2> class Mapa
{
    public:
    Mapa<tip1,tip2>(){;}
    virtual ~Mapa<tip1,tip2>(){;}
    virtual int brojElemenata() const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const tip1& kljuc)=0;
    virtual tip2 &operator[](tip1 x)=0;
    virtual const tip2 operator[](tip1 x) const=0;
};

template <typename tip1, typename tip2> class NizMapa:public Mapa<tip1,tip2>{
    protected:
    int vel, el;
    std::pair<tip1,tip2>** pok;

    public:
    NizMapa<tip1,tip2>():Mapa<tip1,tip2>(),pok(new std::pair<tip1,tip2>*[33333]()),vel(33333),el(0){;}
    ~NizMapa<tip1,tip2>()
    {
        for(int i=0;i<el;i++)
            delete pok[i];
            delete[] pok;
    }

    NizMapa<tip1,tip2>(const NizMapa<tip1,tip2> &x)
    {
        el=x.el;
        vel=x.vel;
        if(x.vel==0)
            pok=nullptr;
        else {
            pok=new std::pair<tip1,tip2>*[vel]();
            for(int i=0;i<x.el;i++)
                pok[i]=new std::pair<tip1,tip2>(*x.pok[i]);
        }
    }
    int brojElemenata() const {return el;}
    int Velicina() const {return vel;}
    void obrisi()
    {
        if(el==0)
            throw std::range_error("Nema elemenata");
        for(int i=0;i<el;i++)
            delete pok[i];
        el=0;
    }
    void obrisi(const tip1& kljuc)
    {
        for(int i=0;i<el;i++)
            if(pok[i]->first==kljuc)
            {
                delete pok[i];
                for(int j=i;j<el-1;j++)
                    pok[j]=pok[j+1];
                    pok[el]=nullptr;
                    el--;
                    return;
            }
            throw std::logic_error("Nema kljuca");
    }
    NizMapa<tip1,tip2>& operator=(const NizMapa<tip1,tip2>& x)
    {
        if(this==&x)
            return *this;
        obrisi();
        el=x.el;
        if(x.Velicina()>Velicina())
        {
            delete[] pok;
            pok=new std::pair<tip1,tip2>* [vel+x.Velicina()]();
            vel=vel+x.vel;
        }
        for(int i=0;i<x.el;i++)
        {
            pok[i]=new std::pair<tip1,tip2>(*x.pok[i]);
        }
        return *this;
    }
    tip2& operator[](tip1 kljuc)
    {
        if(el==vel)
        {
            std::pair<tip1,tip2>** temp=new std::pair<tip1,tip2>*[33333+vel]();
            for(int i=0;i<el;i++)
            {
                temp[i]=new std::pair<tip1,tip2>(*pok[i]);
                delete pok[i];
            }
            delete[] pok;
            vel=vel+33333;
            pok=temp;
            temp=nullptr;
        }
        for(int i=0;i<el;i++)
        {
            if(pok[i]->first==kljuc)
                return pok[i]->second;
        }
        pok[el]=new std::pair<tip1,tip2>(kljuc,tip2());
        el++;
        return pok[el-1]->second;
    }
    const tip2 operator[](tip1 kljuc) const
    {
        for(int i=0;i<el;i++)
            if(pok[i]->first==kljuc)
                return pok[i]->second;
        return tip2();
    }
};
int main()
{
    NizMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
{
        // Konstruktor kopije
	NizMapa<std::string,std::string> m2(m);
        // Operator dodjele
	NizMapa<std::string,std::string> m3;
	m3["Kiseljak"] = "BiH";
	cout << (m3=m).brojElemenata() << " "; // 2
        // Destruktivna samododjela
	cout << (m=m).brojElemenata() << " "; // 2

        // Plitka kopija
	m.obrisi("Sarajevo");
	cout << m2.brojElemenata() << " "; // 2
        cout << m2["Sarajevo"] << " "; // BiH
        cout << m3.brojElemenata() << " "; // 2
        cout << m3["Sarajevo"] << " "; // BiH
}
cout << m.brojElemenata(); // 1
cout << " '" << m["Sarajevo"] << "' "; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Zagreb"] << "'"; // ''
}