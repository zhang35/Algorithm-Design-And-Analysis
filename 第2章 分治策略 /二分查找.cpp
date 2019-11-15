#include <iostream>
using namespace std;

int BinarySearch(int *T, int x, int n);

int main()
{
    int T[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12};
    int x;
    cout << "input interger to be searched:" << endl;
    cin >> x;
    cout << "position: " << BinarySearch(T, x, 10) << endl;
    return 0;
}

//2.1.1 有序数组二分查找
int BinarySearch(int *T, int x, int n){
    int left = 0;
    int right = n - 1;
    while (left <= right){
        int mid = (left + right) / 2;
        if (T[mid] == x){
            return (mid + 1);
        }
        else if (T[mid] < x){
            left = mid + 1;    //注意left可取mid+1，因为mid已经排除
        }
        else{
            right = mid - 1;   //同理right应取mid-1
        }
    }
    return 0;
}
