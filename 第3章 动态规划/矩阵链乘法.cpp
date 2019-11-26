#include <iostream>
using namespace std;

void PrintArray(int **a,int n1, int n2); //打印数组
int MatrixChain(int P[], int n, int **state);
void TraceSolution(int i, int j, int **state);
int main()
{
    int n = 5;  //矩阵个数
    int P[]= {30, 35, 15, 5, 10, 20};
    int **state = new int* [n];
    for (int i=0; i<n; i++){
        state[i] = new int [n];
    }
    int t = MatrixChain(P, n, state);
    cout << "Min multiply times: " << t << endl;
    cout << "Solution is: " << endl;
    TraceSolution(0, n-1, state);
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

//3.2 矩阵连乘问题
int MatrixChain(int P[], int n, int **s){
    int **m = new int* [n];
    for (int i=0; i<n; i++){
        m[i] = new int[n];
        for (int j=0; j<n; j++){
            m[i][j] = 0;
        }
    }

    //m[i][j]表示从i到j的矩阵连乘最小次数，和普通二维数组计算次序不同
    //m[i][j]是一个右上三角矩阵，先知道对角线的值，然后往右上方递推
    //如已知m[0][0],m[1][1],m[2][2]=0, 可求m[0][1], m[1][2]，再求m[0][2]
    for (int r=1; r<n; r++){ //矩阵跨度
        for (int i=0; i<n-r; i++){ //对每个m[i][i+r]，计算i到i+r之间每个k的划分结果
            int j = i + r;  // j取最右矩阵下标
            m[i][j] = m[i+1][j] + P[i] * P[i+1] * P[j+1]; //初始化先取k=i的情况
            s[i][j] = i;
            for (int k=i+1; k<j; k++){ //(Ai...Ak)(Ak+1...Aj)
                int temp = m[i][k] + m[k+1][j] + P[i] * P[k+1] * P[j+1];
                if (temp<m[i][j]){
                    m[i][j] = temp;
                    s[i][j] = k;
                }
            }
        }
    }
    cout << "m[i][j]:" << endl;
    PrintArray(m, n, n);
    cout << "s[i][j]:" << endl;
    PrintArray(s, n, n);

    return m[0][n-1];
}

void TraceSolution(int i, int j, int **state){
    if (j-i<2){
        return;
    }
    cout << state[i][j] << endl;
    TraceSolution(i, state[i][j], state);
    TraceSolution(state[i][j] + 1, j, state);
}
