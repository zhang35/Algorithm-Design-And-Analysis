#include <iostream>
using namespace std;

void PrintArray(int **a,int n1, int n2); //打印数组
int Investment(int m, int n, int **value, int **state);
void TraceSolution(int m, int n, int **state);
int main()
{
    int m = 5;  //钱数
    int n = 4;  //项目数
    int value[6][4] = {{0,0,0,0},{11,0,2,20},{12,5,10,21},{13,10,30,22},{14,15,32,23},{15,20,40,24}};
    int **state = new int* [m+1];  //钱数0-m
    for (int i=0; i<=m; i++){
        state[i] = new int [n];
        for (int j=0; j<n; j++){
            state[i][j] = 0;
        }
    }
    int maxValue = Investment(m, n, (int **)value, state); //注意二维数组传参 
    cout << "maxValue is: \n" << maxValue << endl;
    cout << "Solution is: " << endl;
    TraceSolution(m, n, state);
    return 0;
}

void PrintArray(int **a, int n1, int n2)
{
    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

//3.3.1 投资问题
//设F[m][n]为把m元钱投入前n个项目的最大收益
int Investment(int m, int n, int **value, int **state){
    int **F = new int* [m+1];
    for (int i=0; i<=m; i++){
        F[i] = new int [n];
        for (int j=0; j<n; j++){
            F[i][j] = 0;
        }
    }

    //初始化第一列
    for (int i=1; i<=m; i++){ //把i元都投给第0个项目
        F[i][0] = *((int*)value+i*n);  //不能直接用value[i][j]取值
        state[i][0] = i;
    }
    //递推函数：F[m][n] = max{fn(k) + F[m-k][n]}
    for (int i=1; i<=m; i++){
        for (int j=1; j<n; j++){
            for (int k=0; k<=i; k++){ //k表示投给第j个项目的钱数
                int temp = *((int*)value+k*n+j) + F[i-k][j-1];
                if (temp > F[i][j]){
                    F[i][j] = temp;
                    state[i][j] = k;  //投给第j个项目k元时，收益最大
                }
            }
        }
    }
    cout << "F[i][j]:" << endl;
    PrintArray(F, m+1, n);
    cout << "state[i][j]:" << endl;
    PrintArray(state, m+1, n);
    return F[m][n-1];
}

void TraceSolution(int m, int n, int **state){
    while (m>0){
        int temp = state[m][n-1]; 
        cout << "project" << n << ": " << temp << endl;
        m -= temp;
        n--;
    }
}
