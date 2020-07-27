#include<stdio.h>
  
void merge(int arr[], int l, int m, int r);
  
/* 遍历版归并排序，目标数组arr[0...n-1] */
void mergeSort(int arr[], int n){
   // k为当前待归并子数组的跨度，值为2、4……n/2
   for (int k=2; k<n; k*=2){
       for (int i=0; i<n/k; i++){  //i为第i组待归并数组
           merge(arr, i*k, i*k+k/2, (i+1)*k);
       }
       merge(arr, i*k, i*k+k/2, (i+1)*k);
   }
}

// 以下代码与递归版本的完全一样
/* 归并arr[l..m] 和 arr[m+1..r] */
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    
    /* 将两部分数据复制到临时数组 L[] 和 R[] 中 */
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    /* 将 L[] 和 R[] 中的数据放回arr[l..r]中 */
    i = 0;   //i指向L中首个位置
    j = 0;   //j指向R中首个位置
    k = l;   //k指向arr中首个位置
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else{
            arr[k++] = R[j++];
        }
    }
  
    /* 拷贝L[] R[] 中剩余的元素 */
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void printArray(int A[], int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
  
int main(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
  
    printf("Given array is \n");
    printArray(arr, n);
  
    mergeSort(arr, n);
  
    printf("\nSorted array is \n");
    printArray(arr, n);
    return 0;
}
