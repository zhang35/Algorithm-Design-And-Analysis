#include <iostream>
using namespace std;

void PrintArray(int *a, int n); //打印数组
int MaxSubSum(int *A, int n);

int main()
{
    int A[] = {2, -5, 8, 11, -3, 4, 6};
    int n = 7;
    PrintArray(A, n);
    int mss = MaxSubSum(A, n);
    cout << "max sub Sum is:" << mss << endl;
    return 0;
}

void PrintArray(int *a, int n)
{
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
//3.3.5 最大子段和
//C[i]表示前i项最大子段和
//递推方程C[i] = max{A[i], C[i-1] + A[i]}; 注意不是max{C[i-1], C[i-1]+A[i]}!
int MaxSubSum(int *A, int n){
    int *C = new int[n];
    int begin = 0;
    int end = 0;
    int max = 0;
    if (A[0]>0){
        C[0] = A[0];
        max = A[0];
    }
    else {
        C[0] = 0;
    }

    for (int i=1; i<n; i++){
        if (C[i-1]>0){
            C[i] = A[i] + C[i-1];
        }
        else {
            C[i] = A[i];
            begin = i;  //前面的有副作用，重新开始算

        }
        if (C[i]>max){ //新最大记录诞生，在此截止
            max = C[i];
            end = i;
        }
    }

    cout << "C[i]:" << endl;
    PrintArray(C, n);
    cout << "max sum range is: [" << begin+1 << ", " << end+1 << "]" << endl;
    return max; 
}
