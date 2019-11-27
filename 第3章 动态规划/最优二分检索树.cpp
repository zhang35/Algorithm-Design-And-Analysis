#include <iostream>
using namespace std;

template <class T> void PrintArray(T *a, int n);
template <class T> void PrintArray(T **a, int m, int n);
float OptBST(float *P, int n, int **state);
void TraceSolution(char *S, int **state, int l, int r);

int main()
{
    int n = 5;
    char S[] = {'A', 'B', 'C', 'D', 'E'};
    float P[] = {0.04, 0.1, 0.02, 0.3, 0.02, 0.1, 0.05, 0.2, 0.06, 0.1, 0.01};
    PrintArray(S, n);
    PrintArray(P, 2*n+1);
    cout << endl;
    int **state = new int* [n];
    for (int i=0; i<n; i++){
        state[i] = new int[n]();
    }
    float minCompare = OptBST(P, n, state);
    cout << "min compare times is:\n" << minCompare << endl;
    cout << "tree nodes arrangement:" << endl;
    TraceSolution(S, state, 0, n-1);
    cout << endl;
    delete[] state;
    return 0;
}

template <class T> void PrintArray(T *a, int n) {
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
template <class T> void PrintArray(T **a, int m, int n)
{
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout<<a[i][j]<<" ";
        }
        cout << endl;
    }
    cout<<endl;
}

//3.3.6最优二分检索树
//递推公式：m[i, j] = min{m[i, k-1] + m[k+1, j] + w[i, j]},k表示以k为根,w[i,j]为i到j叶子和节点概率和
//因为两棵子树组合成一棵二叉树时，其所有节点深度都增加1，再加上节点k的概率，正好增加了w[i, j]
//和矩阵链问题类似，都是右上三角矩阵，按对角线填充
float OptBST(float *P, int n, int **state){
    float **m = new float* [n](); //i到j生成最优二分检索树平均次数
    float **w = new float* [n](); //i到j所有叶子和节点概率和
    for (int i=0; i<n; i++){
        m[i] = new float[n]();
        w[i] = new float[n]();
        w[i][i] = P[2*i] + P[2*i+1] + P[2*i+2];
        m[i][i] = w[i][i];
        state[i][i] = i;
    }

    for (int len=1; len<n; len++){
        for (int i=0; i<n-len; i++){
            int j=i+len;
            m[i][j] = m[i+1][j];  //k=i的情况, m[i][i-1]=0
            w[i][j] = w[i][j-1] + P[2*j+1] + P[2*j+2];
            state[i][j] = i;
            for (int k=i+1; k<=j; k++){
                float temp = m[i][k-1];
                if (k!=j){ //k=j时，m[j+1][j]=1
                    temp += m[k+1][j];
                }
               if (temp < m[i][j]){
                   m[i][j] = temp;
                   state[i][j] = k;
               }
            }
            m[i][j] += w[i][j];
        }
    }
    cout << "m[i][j]:" << endl;
    PrintArray(m, n, n);
    cout << "state[i][j]:" << endl;
    PrintArray(state, n, n);
    
    float optBST = m[0][n-1];
    delete[] m;
    delete[] w;
    return optBST;
}

void TraceSolution(char *S, int **state, int l, int r){
    if (l>r){
        return;
    }
    int rootIndex = state[l][r];
    cout << S[rootIndex] << " ";
    TraceSolution(S, state, l, rootIndex-1);
    TraceSolution(S, state, rootIndex+1, r);
}
