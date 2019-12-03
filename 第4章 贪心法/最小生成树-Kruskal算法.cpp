#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

struct Edge{
    int v1;
    int v2;
    int w;
};

int Kruskal(int *V, int **E, int n);
void PrintArray(int *a, int n); //打印数组

int main()
{
    int n = 8;
    int V[] = {1, 2, 3, 4, 5, 6, 7, 8};
    //不考虑环
    //如果两个顶点有平行边，取其中最短的一条
    int E[][8] = {{INT_MAX, 2, 3, INT_MAX, INT_MAX, INT_MAX,INT_MAX,INT_MAX},
        {2, INT_MAX, 4, 18, INT_MAX, INT_MAX, 7, INT_MAX},
        {3, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8},
        {INT_MAX, 18, INT_MAX, INT_MAX, 5, 3, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 5, INT_MAX, 4, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 3, 4, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1},
        {INT_MAX, INT_MAX, 8, INT_MAX, INT_MAX, INT_MAX, 1, INT_MAX}};

    int minCost = Kruskal(V, (int**)E, n);
    cout << "Min cost is: " << minCost << endl;
    return 0;
}

void PrintArray(vector<int> a) {
    for (vector<int>::iterator it=a.begin(); it!=a.end(); ++it){
        cout << *it << " ";
    }
    cout<<endl;
}

bool cmp(Edge e1, Edge e2){
    return e1.w < e2.w;
}

//4.4.2 最小生成树 Kruskal算法
int Kruskal(int *V, int **E, int n){
    vector<Edge> G;
    int minCost = 0;
    for(int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            int weight = *((int*)E + i*n + j);//取i, j, E[i][j]
            if (weight!=INT_MAX){
                Edge *e = new Edge();
                e->v1 = i;
                e->v2 = j;
                e->w = weight;
                G.push_back(*e);
            }
        }
    }
    sort(G.begin(), G.end(), cmp);
    cout << "Edges:" << endl;
    for (vector<Edge>::iterator it=G.begin(); it!=G.end(); ++it){
        cout << V[it->v1] << "-" << V[it->v2] << " weight: " << it->w << endl;
    }

    vector<int> Find(n); //Find[i]表示i的连通分支标记
    vector<int> BranchSize(n); //BranchSize[i]表示标记为i的连通分支节点数
    for (int i=0; i<n; i++) {
        Find[i] = i+1;
        BranchSize[i] = 1;
    }
    cout << "Find[i]:" << endl;
    PrintArray(Find);
    int count = 0;
    for (vector<Edge>::iterator it=G.begin(); count<n-1 && it!=G.end(); ++it){
        int m1 = Find[it->v1];
        int m2 = Find[it->v2];
        if (m1!=m2){ //不在同一个连通分支
            cout << "add edge: " << V[it->v1] << "-" << V[it->v2] << " weight: " << it->w << endl;
            minCost += it->w;
            if (BranchSize[m1]>BranchSize[m2]){ //使m2指示规模较大的分支
                int temp = m1;
                m1 = m2;
                m2 = temp;
            }
            for (int i=0; i<n; i++) { //将小分支合并到大分枝
                if (Find[i]==m1){
                    Find[i] = m2;
                }
            }
            BranchSize[m2] += BranchSize[m1];
            BranchSize[m1] = 0;
            count++;
        }
        cout << "Find[i]:" << endl;
        PrintArray(Find);
    }
    return minCost;
}
