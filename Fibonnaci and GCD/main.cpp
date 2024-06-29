#include <iostream>
#include <stdexcept>

using namespace std;

int fib(int n)
{
    if (n<=1)
        return n;
    return fib(n-1)+fib(n-2);
}

int fib_petlja(int n)
{
    if(n<=1)
        return n;
        
    int prvi(0),drugi(1),rez(0);
    for(int i(2);i<=n;i++)
    {
    rez=prvi+drugi;
    prvi=drugi;
    drugi=rez;
    }
    return rez;
}

int fib2_0(int n, int prvi=0, int drugi=1)
{
    if(n==0)
        return prvi;
    else 
        if(n==1)
            return drugi;

    return fib2_0(n-1,drugi,drugi+prvi);
}

int nzd(int prvi, int drugi)
{
    if(drugi==0)
        return prvi;
    return nzd(drugi,prvi%drugi);
}


int main()
{   
    cout << nzd(101,12) << std::endl;
    cout << fib2_0(20) << std::endl;
    cout << nzd(6, 561) << std::endl;
}