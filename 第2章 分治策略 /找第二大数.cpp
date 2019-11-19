#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

void P(int a[],int n); //打印数组
int FindSecond(int *S, int n);

int main()
{
    int n = 10;
    int S[]= {1,3,5,7,9,2,4,6,8,10};
    P(S, n);
    cout << "Second max is: " << FindSecond(S, n)  << endl;
    return 0;
}
void P(int a[],int n)
{
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

//2.4.2 使用锦标赛算，第二大元素只能在与最大元素max直接比较输掉的元素中
//用链表记录所有元素淘汰的对手，找到max后，遍历其链表找出其中最大的即可
int FindSecond(int *S, int n){
    if (n<2){
        return 0;
    }
    list<int> loserList[n];
    int maxValue = S[0];
    int maxIndex = 0;
    for (int i=1; i<n; i++) {
        if (S[i]>maxValue){
            loserList[i].push_back(maxValue);
            maxValue = S[i];
            maxIndex = i;
        }
        else{
            loserList[maxValue].push_back(S[i]);
        }
    }

    for (int i=0; i<n; i++){
        cout << S[i] << ": ";
        for (list<int>::iterator it=loserList[i].begin(); it!=loserList[i].end(); it++){
            cout << *it << "->";
        }
        cout << endl;
    }

    list<int>::iterator it=loserList[maxIndex].begin();
    int secondMax = *it;
    it++;
    while (it!=loserList[maxIndex].end()){
        secondMax = max(*it, secondMax);
        it++;
    }
    return secondMax;
}
