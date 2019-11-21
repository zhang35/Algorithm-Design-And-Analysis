#include <iostream>
#include <algorithm>
using namespace std;

void P(int a[],int n); //打印数组
int MatrixChain(int S[], int n);

int main()
{
    int n = 5;  //矩阵个数
    int S[]= {30, 35, 15, 5, 10, 20};
    int state[n][n];
    //cout << "Min multiply times: " << MatrixChain(S, n)  << endl;
    MatrixChain(S, n);
    return 0;
}

void P(int **a,int n)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; i++)
            cout<<a[i][j]<<" ";
    cout<<endl;
}

int MatrixChain(int S[], int n){
    int **m = new int* [n-1];
    int **s = new int* [n-1];
    for (int i=0; i<n-1; i++){
        m[i] = new int[n-1];
        s[i] = new int[n-1];
        for (int j=0; j<n-1; j++){
            m[i][j] = 0;
            s[i][j] = 0;
        }
    }

    //初始化第一行
    for (int i=0; i<n-1; i++){
        m[0][i] = S[i] * S[i+1] * S[i+2]; //m[0][i]代表跨度为1，
    }
    for (int j=2; j<n; j++){ //矩阵跨度
        for (int i=0; i<n-j; i++){

            int n1 = m[j-2][i] + S[i] * S[i+j] * S[i+j+1];
            int n2 = m[j-2][i+1] + S[i] * S[i+1] * S[i+j+1];
            cout << j-1 << " " << i << " "<< n1 << " " << n2 << endl;
            if (n1<n2){
                m[j-1][i] = n1;
                s[j-1][i] = i + j - 1; //i+j-1处右侧加括号
            }
            else {
                m[j-1][i] = n2;
                s[j-1][i] = i;  //i处右侧加括号
            }
        }
    }
    for (int i=0; i<n-1; i++){ 
        for (int j=0; j<n-1; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
/*    for (int i=0; i<n-1; i++){ */
        //for (int j=0; j<n-1; j++){
            //cout << s[i][j] << " ";
        //}
        //cout << endl;
    /*}*/
    return 0;
}
