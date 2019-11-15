#include <iostream>
using namespace std;

int Fib(int n); //动态规划求斐波那契数列

int main()
{
    cout << "input index of Fibonacci:" << endl;
    int n;
    cin >> n;
    cout << Fib(n) << endl;
    return 0;
}

int Fib(int n){
    if (n<=1){
        return n;
    }
    
    //备忘录。当然也可以只用3个变量，循环利用。
    int* memo = new int[n+1];
    
    memo[0] = 0;
    memo[1] = 1;
    
    for (int i=2; i<=n; i++){
        memo[i] = memo[i-1] + memo[i-2];
    }
    
    return memo[n];
}
