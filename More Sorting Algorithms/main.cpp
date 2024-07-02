#include <iostream>
#include <iomanip>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm> 

using  namespace std;

int vectorMax(vector<int> v)
{
    int vel=v.size();
    int m_prvi = v[0];
    for (int i = 1; i < vel; i++)
        if (v[i] > m_prvi)
            m_prvi = v[i];
    return m_prvi;
}

 void countSort(std::vector<int> &v, int exp)
{
    std::vector<int> izlaz=v;
    int vel=v.size();
    int i = 0, broji[10] = { 0 };
    for (i = 0; i < vel; i++)
        broji[(v[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        broji[i] += broji[i - 1];
    for (i = vel - 1; i >= 0; i--) {
        izlaz[broji[(v[i] / exp) % 10] - 1] = v[i];
        broji[(v[i] / exp) % 10]--;
    }
    for (i = 0; i < vel; i++)
        v[i] = izlaz[i];
} 

void radixSort(vector<int>&v)
{
    int temp = vectorMax(v);
    for (int exp = 1; temp / exp > 0; exp = exp * 10)
        countSort(v,exp);
}

void swapp(vector<int> &v,int i, int j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int roditelj(int i){return (i-1)/2;}
int l_dijete(int i){return 2*i+1;}
int d_dijete(int i){return 2*i+2;}

void popravi_dolje(vector <int> &v , int i, int vel){

        while(!(i>=vel/2 && i<vel)){
            int veci = l_dijete(i);
            int des = d_dijete(i);
            if((des < vel) && (v[des]>v[veci])) veci = des;
            if(v[i]>v[veci]) return;
            swapp(v,i,veci);
            i = veci;
        }
}

void popravi_gore(vector <int> &v , int i){
    while((i!=0) && (v[i]>v[roditelj(i)])){
    swapp(v,i,roditelj(i));
    i = roditelj(i);
    }
}

int izbaciPrvi(vector<int> &v, int &velicina){
    if(v.size()==0)
        throw std::domain_error("Nema");
   --velicina;
    swapp(v,0,velicina); 
    if(velicina!=0)popravi_dolje(v, 0,velicina);
    return v[velicina];
}

void umetniUGomilu(vector<int> &v, int umetnuti, int &velicina){
    v.push_back(umetnuti);
    ++velicina;
    popravi_gore(v, velicina-1);
}

void stvoriGomilu(vector<int> &v){
    int vel = v.size();
    for(int i = std::floor((vel/2.));i>=0;i--)
    popravi_dolje(v, i,vel);
}

void gomilaSort(vector<int> &v){
    stvoriGomilu(v);
    int vel = v.size();
    for(int i=vel-1;i>0;i--){       
        swapp(v,0,i);       
        popravi_dolje(v, 0, i);}
}

int main()
{
    vector<int> a;
    vector<int> b;
    a.push_back(545);
    a.push_back(1545);
    a.push_back(4536);
    a.push_back(124121);
    a.push_back(1);
    a.push_back(95468);
    for(int i=0;i<10000;i+=13){
        a.push_back(i);
    }
    for(int i=0;i<a.size();i++){
        b.push_back(a[i]);
    }
    radixSort(a);
    sort(b.begin(),b.end());
    bool testOk = true;
    for(int i(0);i<a.size();i++){
        if(a[i]!=b[i]) testOk = false;;
    }
    if(testOk) cout<<"OK";
    
}