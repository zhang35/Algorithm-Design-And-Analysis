#include <iostream>
using namespace std;

int Knapsack(int k, int y, int *w, int *v, int **I);
int* KnapsackTrackSolution(int k, int y, int *w, int **I);

int main()
{
    int k = 4;
    int y = 10;
    int V[4] = {1, 3, 5, 9};
    int W[4] = {2, 3, 4, 7};
    int **state = new int* [k];
    for (int i=0; i<k; i++){
        state[i] = new int[y];
        //顺便初始化
        for (int j=0; j<y; j++){
            state[i][j] = 0;
        }
    }
    int max = Knapsack(k, y, W, V, state);
    cout << "max is :" << max << endl;
    
    int *solution = KnapsackTrackSolution(k, y, W, state);
    for (int i=0; i<k; i++){
        cout << "item" << i+1 << ":"<< solution[i] << endl;
    }
    return 0;
}

//3.3.2 背包问题
//k种物品，背包容量为y，物品重量数组为w，物品价值数组为v，
//标记函数I(k)(y)：装前k种物品，容量为y时，达到最大值时装入的最大标号
int Knapsack(int k, int y, int *w, int *v, int **I){
    if (k<=0 || y <=0){
        return 0;
    }
    //动态申请二维数组空间，k行，capacity列。因为最多要遍历每个东西1……k，分别装1……capacity个的情况
    int **F = new int* [k];
    for (int i=0; i<k; i++){
        //每行要生成y+1长的数组，因为为了能迭代，需要有容量为0时的情况，值为0。
        F[i] = new int[y+1];
        //顺便初始化
        for (int j=0; j<=y; j++){
            F[i][j] = 0;
        }
    }
    
    // 以下分析过程，来自屈婉玲《算法设计与分析》
    //设一组解是<x1，x2，……，xn>，xi表示装第i种物品的个数
    //目标函数是max(∑vi*xi) 约束条件是∑wi*xi<=b
    //子问题由y和k确定，k: 装前k种k物品，y：容量为y。
    //子问题计算顺序：
    //    k=1, 2, 3, ..., n
    //        对于给定的k，y=1, 2, 3,...,n
    
    //优化函数递推方程F(k)(y):装前k种物品，容量为y，背包达到的最大价值
    // F(k)(y) = max{ F(k-1)(y), F(k)(y-wk) + vk}
    // F(0)(y) = 0, 0<=y<=b, F(k)(0)=0, 0<=k<=n
    //   前一项是不装第k种，仍然只用前k-1种装。
    //   关键是理解后一项。先装1个第k种，产生收益vk；剩下的容量为y-wk，继续用前k种装，即F(k)(y-wk)
    // 例如：F(1)(y) = y/w1 * v1, 若y<0，则记F(k)(y) = -♾
    
    // 标记函数I(k)(y)：装前k种物品，容量为y时，达到最大值时装入的最大标号。
    // 若优化函数的max取左侧，则I(k)(y) = I(k-1)(y)；若取右侧，则I(k)(y) = k
    // y<w1时，I(1)(y) = 0; 否则I(1)(y) = 1，即起码能装一个1号物品。
    
    //计算i=0的情况
    for (int j=1; j<=y; j++){
        F[0][j] = v[0] * (j/w[0]);
        if (F[0][j]>0){
            I[0][j-1] = 1;
        }
    }
    //计算装前i种东西，容量为j+1时最大价值
    //F[i][j-w[i]] + v[i] 可能出现j-w[i]=0的情况，也是允许的，表示装1个第i种正好满。
    // = F[i][0] + v[i] = v[i]
    for (int i=1; i<k; i++){
        for (int j=1; j<=y; j++){
            //装不下时
            if (j-w[i] < 0){
                F[i][j] = F[i-1][j];
                I[i][j-1] = I[i-1][j-1];
            }
            else{
                if (F[i-1][j] > (F[i][j-w[i]] + v[i])){
                    F[i][j] = F[i-1][j];
                    I[i][j-1] = I[i-1][j-1];
                }
                else{
                    F[i][j] = F[i][j-w[i]] + v[i];
                    I[i][j-1] = i + 1;
                }
         
            }
        }
    }
    
    for (int i=0; i<k; i++){
        for (int j=1; j<=y; j++){
            cout << F[i][j] << " ";
        }
        cout << endl;
    }

    for (int i=0; i<k; i++){
        for (int j=0; j<y; j++){
            cout << I[i][j] << " ";
        }
        cout << endl;
    }
    return F[k-1][y];
}

//追溯解
int* KnapsackTrackSolution(int k, int y, int *w, int **I){
    int *solution = new int[k];
    for (int i=0; i<k; i++){
        solution[i] = 0;
    }
    int si = I[k-1][y-1];
    while(y>0 && si>0){
        solution[si-1]++;
        y -= w[si-1];
        si = I[k-1][y-1];
    }
    
    return solution;
}
