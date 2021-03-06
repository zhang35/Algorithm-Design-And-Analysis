#include<stdio.h>

void merge(int arr[], int l, int m, int r);

void mergeSort(int arr[], int l, int r) {
   if (l < r){
      int m = l+(r-l)/2;  // 相当于 (l+r)/2，但能防止过大的l、h导致溢出
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
}

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
        R[j] = arr[m + 1+ j];
        
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

void printArray(int A[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
  
    printf("Given array is \n");
    printArray(arr, arr_size);
  
    mergeSort(arr, 0, arr_size - 1);
  
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
