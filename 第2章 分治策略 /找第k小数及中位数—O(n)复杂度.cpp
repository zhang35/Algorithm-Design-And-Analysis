#include <iostream>
using namespace std;

void P(int a[],int n); //打印数组
int SelectK(int *S, int l, int r, int k);//找第k小数
int Median(int *S, int l, int r);//找中位数

int main()
{
    int n = 10;
    int S[]= {1,3,5,7,9,2,4,6,8,10};
    P(S, 10);
    int k;
    cout << "input k:";
    cin >> k;
    cout << "the " << k << "th min number is: " << SelectK(S, 0, n-1, k-1) << endl;
    //Median(S, 0, n-1);
    cout << "Median is: " << Median(S, 0, n-1) << endl;
    return 0;
}
void P(int a[],int n)
{
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
int Partition(int *S, int l, int r){
    int i = l;
    int j = r;
    int x = S[l];
    while (i<j){
        while (i<j && S[j]>=x){
            j--;
        }
        if (i<j){
            S[i++] = S[j];
        }
        while (i<j && S[i]<=x){
            i++;
        }
        if (i<j){
            S[j--] = S[i];
        }
    }
    S[i] = x;
    return i;
}
//2.4.2 找第k小数,等价于找到一个位置为k的元素，前面的都比它小，后面的都比它大
//采用类似于快速排序的划分方法，但根据情况每次只处理其中一边，通过计算（《算法导论》p109）其平均复杂度为O(n)
//(书中P43方法:先将S划分成5个一组，每组找中位数。但是怎么找中位数呢！问题死循环了！所以使用了这种易懂的方法)
int SelectK(int *S, int l, int r, int k){
    int pivot = Partition(S, l, r);
    if (pivot==k){ //找到了位置k，前面的都比它小，后面的都比它大
       return S[pivot];
    }
    else if(pivot>k){ //pivot后面的都比它大，可以忽略了
        return SelectK(S, l, pivot-1, k); //划分前半部分
    }
    else{ //pivot前面的都比它小，也可以忽略了
        return SelectK(S, pivot+1, r, k); //划分后半部分
    }
}

//找中位数，如果数组的个数是偶数个，则返回排序后数组的第N/2个数
int Median(int *S, int l, int r){
    return SelectK(S, l, r, (r-l)/2);
}

