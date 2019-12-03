#include <iostream>
#include <climits>
using namespace std;

int Prime(int *V, int **E, int n);

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
    int minCost = Prime(V, (int**)E, n);
    cout << "Min cost is: " << minCost << endl;
    return 0;
}

//4.4.2 最小生成树 Prime算法
int Prime(int *V, int **E, int n){
    int *TV = new int[n]; //记录加入生成树的节点下标
    TV[0] = 0;  //加入第0个节点
    cout << "add vertex: " << V[0] << endl;
    int len = 1;  //记录加入生成树的节点数
    int minCost = 0;
    while (len<n) { 
        int minE = INT_MAX;
        int tempI = 0;
        for (int i=0; i<len; i++) {  //对于当前生成树中的每个节点
            int vi = TV[i]; 
            for (int j=0; j<n; j++){ //不能先把初值取j=0，然后从j=1比较。初值应为INT_MAX 
                //过滤掉已经在生成树中的节点，防止出现回路
                bool flag = true;
                for (int k=0; k<len; k++){ 
                    if (TV[k]==j){
                        flag = false;
                        break;
                    }
                }
                if (flag){
                    int tempE = *((int*)E + vi*n + j);  //取第j个元素
                    if (tempE < minE){
                        minE = tempE;
                        TV[len] = j;
                        tempI = vi; //记录生成树中哪个节点进行了扩张
                    }
                }
            }
        }
        cout << "add vertex: " << V[TV[len]] << endl;
        cout << "add edge: " << V[tempI] << "-" << V[TV[len]] << " length: " << minE << endl;
        minCost += minE;
        len++;
    }
    return minCost;
}
