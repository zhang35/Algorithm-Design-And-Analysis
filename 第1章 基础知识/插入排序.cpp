#include <iostream>
using namespace std;

void InsertSort(int *array, int n);
void P(int a[],int n); //打印数组

int main()
{
    //int a[]= {72,6,57,88,60,42,83,73,48,85};
    int a[]= {10,9,8,7,6,5,4,3,2,1};
    P(a,10);
    InsertSort(a, 10);
    P(a,10);
    return 0;
}

void P(int a[],int n)
{
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

//1.3.3 插入排序
void InsertSort(int *array, int n){
    for (int i=1; i<n; i++){
        int temp = array[i];
        int j;
        //i指示待排元素，j指示插入位置。注意：j可以取到0！
        for (j=i-1; j>=0 && array[j]>temp; j--){
           array[j+1] = array[j]; //依次后移挪位置
        }
        array[j+1] = temp; //因为退出循环时还有次j--，插入位置应为j+1
     }
}
