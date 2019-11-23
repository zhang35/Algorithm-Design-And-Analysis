#include <iostream>
#include <string>
using namespace std;

void PrintArray(int **a,int n1, int n2); //打印数组o
string LCS(string X, string Y);

int main()
{
    string X = "ABCBDAB";
    string Y = "BDCABA";
    string lcs = LCS(X, Y);
    cout << "LCS is: " << lcs << endl;
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
//3.3.3 最长公共子序列LCS
//递推函数C[i][j]表示字符串X[m],Y[n]的子串X[0...i]，Y[0...j]的最长公共子序列长度
//两个string之间的事，为什么要用int型的递推函数C[i][j]呢？因为要找“最长”。
string LCS(string X, string Y){
    unsigned long m = X.size();
    unsigned long n = Y.size();
    int **C = new int* [m+1];
    int **state = new int* [m+1];
    for (int i=0; i<=m; i++){
        C[i] = new int[n+1];
        state[i] = new int[n+1];
        for (int j=0; j<=n; j++){
            C[i][j] = 0;
            state[i][j] = 0;
        }
    } 

    for (int i=1; i<=m; i++){
        for (int j=1; j<=n; j++){
            if (X[i-1]==Y[j-1]){  //此处容易出错！注意i、j表示的是第几个字符，要从0开始取
                C[i][j] = C[i-1][j-1] + 1;
                state[i][j] = 3;
            }
            else{
               int c1 = C[i-1][j];
               int c2 = C[i][j-1];
               if (c1>=c2){
                   C[i][j] = c1;
                   state[i][j] = 1;
               }
               else{
                   C[i][j] = c2;
                   state[i][j] = 2;
               }
            }
        }
    }
    
    cout << "C[i][j]:" << endl;
    PrintArray(C, m+1, n+1);
    cout << "state[i][j]:" << endl;
    PrintArray(state, m+1, n+1);

    string lcs = "";
    int i = m;
    int j = n;
    while (i>0 && j>0){
        if (state[i][j] == 3){
            //string& insert (size_t pos, size_t n, char c);
            lcs.insert(0, 1, X[i-1]); //insert比+=效率高
            i--;
            j--;
        }
        else if (state[i][j] == 1){
           i--; 
        }
        else if (state[i][j] == 2){
            j--;
        }
    }
    return lcs;
}
