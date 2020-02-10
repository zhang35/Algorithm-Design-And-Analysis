#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void BFS(int s, int t, vector<vector<int> > &C, vector<vector<int> > &F, vector<int> &L){
    int n = L.size();
    vector<int> D(n, INT_MAX);
    vector<bool> visited(n);
    L[s] = 0;
    while(1) {
        //顺序查找第一个已标号且未搜索过的顶点
        int i = 0;
        while (i<n && (visited[i] || L[i]==INT_MAX)){
            i++;
        }
        if (i==n){  //若没有已标号未搜索过的顶点
            return;
        }
        visited[i] = true;
        for (int j=0; j<n; j++){
            if (L[j]==INT_MAX){  //未标号且有路径
                if (F[i][j]<C[i][j]){  //前向边，F[i][j]>=0，所以隐含了C[i][j]>0
                    D[j] = min(D[i], C[i][j]-F[i][j]);
                    L[j] = i;
                }
                else if(F[j][i]>0){  //后向边
                    D[j] = min(D[i], F[j][i]);
                    L[j] = -i;
                }
                //找到增广路径，从t回溯，修改流量，结束BFS
                if (L[t]!=INT_MAX){
                    do {
                        if (L[j]>=0){
                            F[L[j]][j] += D[t];
                            j = L[j];
                        }
                        else{
                            F[j][-L[j]] -= D[t];
                            j = -L[j];
                        }
                    }while(j!=s);
                    return;
                }
            }
        }
    }
}
int main(){
    int n, m, s, t;
    cin >> n >> m;
    s = 0;
    t = n - 1;
    vector<vector<int> > C(n, vector<int>(n));  //邻接矩阵，值为容量
    for (int i=0; i<m; i++){
        int j, k, c;
        cin >> j >> k >> c;
        C[j][k] = c;
    }

    vector<vector<int> > F(n, vector<int>(n));//流
    vector<int> L(n, INT_MAX);//标号，L：流量来源
    do{
        fill(L.begin(), L.end(), INT_MAX);
        BFS(s, t, C, F, L);
    }while(L[t]!=INT_MAX);

    cout << "Maximum flow:" << endl;
    int totalFlow = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (C[i][j]>0){  //i到j
                if (i==0){
                    totalFlow += F[i][j];
                }
                cout << i << " " << j << " " << F[i][j] << endl;
            }
        }
    }
    cout << "Total flow:\n" << totalFlow << endl;

    cout << "Minimum cut:" << endl;
    vector<vector<int> > A(2);
    for (int i=0; i<n; i++){
        if (L[i]!=INT_MAX){
            A[0].push_back(i);
        }
        else{
            A[1].push_back(i);
        }
    }
    for (int i=0; i<2; i++){
        for (int j=0; j<A[i].size(); j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


