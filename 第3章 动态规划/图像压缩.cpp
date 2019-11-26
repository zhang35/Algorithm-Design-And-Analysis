#include <iostream>
#include <cmath>
#include <stack>
using namespace std;

void PrintArray(int *a, int n); //打印数组
int Compress(int *P, int n, int *l);
void Traceback(int *l, int n);

int main()
{
    int P[] = {10, 12, 15, 255, 1, 2};
    int n = 6;
    PrintArray(P, n);
    int *l = new int[n+1];  //l[i]表示达到最小位数时最后一段的项数
    int minBit = Compress(P, n, l);
    cout << "min bit length is:\n" << minBit << endl;
    Traceback(l, n);
    return 0;
}

void PrintArray(int *a, int n)
{
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
int Bits(int n){
    if (n==1){
        return 1;
    }
    return ceil(log2(n+1));
}
//3.3.4 图像压缩
//S[i]表示前i项(i是序数，非下标)最短压缩长度, b[i]表示前i项最大位数
//递推方程S[i] = min{S[k]+(i-k)*log(max{Pk+1...Pi})}, 0<=k<i(要保证能遍历所有情况)
//递推方程b[i] = max{b[i-1], log(Pi)}
int Compress(int *P, int n, int *l){
    int header = 11;
    int *S = new int[n+1];
    int *b = new int[n+1];  //每项所占位数
    S[0] = 0;
    b[0] = 0;

    //需要注意加header的时机。
    //当k=0时只需要一个header，当k>0时需要额外一个header
    //本来应该是S[i] = S[i-1] + b[i] + header; 
    //int temp = S[k] + (i-k) * maxBit + header;
    //二者比较时可先同时忽略header，最后再加上
    for (int i=1; i<=n; i++){
        b[i] = Bits(P[i-1]);
        S[i] = S[i-1] + b[i]; //k=i-1时
        l[i] = 1;
        for (int k=0; k<i-1; k++){
            //找出k+1...i项中需要的最大位数
            int maxBit = b[k+1];
            for (int l=k+2; l<=i; l++){
                if (b[l]>maxBit){
                    maxBit = b[l];
                }
            }
            int temp = S[k] + (i-k) * maxBit;
            if (S[i]>temp) {
                S[i] = temp;
                l[i] = i - k;
            }
        }
        S[i] += header;
    }

    cout << "S[i]:" << endl;
    PrintArray(S, n+1);
    cout << "l[i]:" << endl;
    PrintArray(l, n+1);
    return S[n]; 
}

void Traceback(int *l, int n){
    stack<int> s;
    cout << "division is:"<< endl;
    while (n>0){
        s.push(l[n]);
        n -= l[n];
    }
    while (s.size()>0){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}
