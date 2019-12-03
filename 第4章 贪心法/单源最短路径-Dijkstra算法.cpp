#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

vector<int> Dijkstra(vector<int> V, vector<vector<int> > E, int s, int n);
void PrintArray(vector<int> a);//打印数组

int main()
{
    int n = 6;
    vector<int> V = {1, 2, 3, 4, 5, 6};
    vector<vector<int> > E = {{0, 10, INT_MAX, INT_MAX, INT_MAX, 3},
        {INT_MAX, 0, 7, 5, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX},
        {3, INT_MAX, 4, 0, 7, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX},
        {INT_MAX, 2, INT_MAX, 6, 1, 0}};

    int s = 0;  //源节点下标
    vector<int> dist = Dijkstra(V, E, s, n);
    cout << "Min distance is: " << endl;
    for (int i=0; i<n; i++){
        cout << V[s] << "->" << V[i] << ": " << dist[i] << endl;
    }
    return 0;
}

void PrintArray(vector<int> a) {
    for (vector<int>::iterator it=a.begin(); it!=a.end(); ++it){
        if (*it == INT_MAX){
            cout << "∞ ";
        }
        else{
            cout << *it << " ";
        }
    }
    cout<<endl;
}

//4.3.3 单源最短路径 Dijkstra算法
vector<int> Dijkstra(vector<int> V, vector<vector<int> > E, int s, int n){
    vector<int> dist(n); //表示源点s到每个节点的最短距离 
    for (int i=0; i<n; i++){
        dist[i] = E[s][i];
    }
    cout << "dist[i]: ";
    PrintArray(dist);

    vector<int> L(n, s);  //L[i]表示s到i最短路径上i上一个节点标号,均初始化为s
    vector<bool> flag(n);  //标记是否已被选入
    flag[s] = true;

    //每次循环添加1个节点，直到添加n-1个节点为止
    for (int count=0; count<n-1; count++){
        //找出最小值
        int minDist = INT_MAX;
        int minI = s;
        //找到未被选取节点中，dist[i]最小的
        for (int i=0; i<n; i++){
            if (!flag[i] && dist[i]<minDist){ 
                minDist = dist[i];
                minI = i;
            }
        }
        flag[minI] = true;
        cout << "add vertex: " << V[minI] << endl;
        //加入节点minI后，更新未被选取节点的dist[i]和L[i]
        for (int i=0; i<n; i++){
            if (!flag[i] && E[minI][i]!=INT_MAX){  //还未被选取，且有边存在
                int tempDist = minDist + E[minI][i];
                if (tempDist< dist[i]){
                    dist[i] = tempDist;
                    L[i] = minI;
                }
            }
        }
        cout << "dist[i]: ";
        PrintArray(dist);
    }
    return dist;
}
