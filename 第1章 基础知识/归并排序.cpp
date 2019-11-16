#include <iostream>
using namespace std;

void MergeSort(int *array, int p, int r);
void P(int a[],int n); //打印数组

int main()
{
    //int a[]= {72,6,57,88,60,42,83,73,48,85};
    int a[]= {10,9,8,7,6,5,4,3,2,1};
    P(a,10);
    MergeSort(a, 0, 9);//注意最后一个参数是n-1!!!!!
    P(a,10);
    return 0;
}

void P(int a[],int n)
{
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

//1.3.3 归并排序
//p...m, m+1...r为两部分排好的递增数列，把它们合并到一起
void Merge(int *array, int p, int m, int r){
    int lenA = m - p + 1;
    int lenB = r - m;
    int *A = new int[lenA];
    int *B = new int[lenB];
    memcpy(A, array+p, lenA*sizeof(int));
    memcpy(B, array+m+1, lenB*sizeof(int)); //注意参数2拷贝位置，不是array+p+m+1
    cout << "sorting:" << endl;
    P(A, lenA);
    P(B, lenB);
    int i = 0; //指示A中元素
    int j = 0; //指示B中元素
    int k = p; //指示array中待放位置，注意k的起始位置
    while (i<lenA && j<lenB) {
        if (A[i]<B[j]){
            array[k] = A[i];
            i++;
        }
        else{
            array[k] = B[j];
            j++;
        }
        k++;
    }
    //把没拷完的数组，继续往array中拷
    if (lenA-i>0){
        memcpy(array+k, A+i, (lenA-i)*sizeof(int));
    }
    else{
        memcpy(array+k, B+j, (lenB-j)*sizeof(int));
    }
    delete[] A;  //回收数组要用delete[] x,回收单个对象是delete x
    delete[] B;
}

void MergeSort(int *array, int p, int r){
    if (r>p){
        int m = (p + r) / 2;
        MergeSort(array, p, m); 
        MergeSort(array, m+1, r);
        Merge(array, p, m, r);
    }
}

