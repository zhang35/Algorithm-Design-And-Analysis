#include <iostream>
using namespace std;

int FibRec(int n); //递归法求斐波那契数列

int main()
{
    cout << "input index of Fibonacci:" << endl;
    int n;
    cin >> n;
    cout << FibRec(n) << endl;
    return 0;
}

//递归法
int FibRec(int n){
    if (n<=1){
        return n;
    }
    if (n==2){
        return 1;
    }
    
    return FibRec(n-1) + FibRec(n-2);
}
