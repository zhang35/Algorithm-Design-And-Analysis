#include <iostream>
using namespace std;

int Euclid(int m, int n);

int main()
{
    cout << "input m and n:" << endl;
    int m, n;
    cin >> m >> n;
    cout << "GCD is: " << Euclid(m, n) << endl;
    return 0;
}

//1.2 欧几里得法求最大公约数
int Euclid(int m, int n){
    int r;
    while (n!=0 ){
       r = m % n;
       m = n;
       n = r;
    }
    return m;
}
