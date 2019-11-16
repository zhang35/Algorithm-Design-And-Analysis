#include <iostream>
using namespace std;

void Hanoi(char A, char B, char C, int n);

int main()
{
    cout << "input n:" << endl;
    int n;
    cin >> n;
    char A = 'A';
    char B = 'B';
    char C = 'C';
    Hanoi(A, B, C, n);
    return 0;
}

//1.3.3 汉诺塔问题
//将n个圆盘从A挪到C，以B为跳板
void Hanoi(char A, char B, char C, int n){
    //只有1个的情况，直接挪过去
    if (n==1){
        cout << "move:" << A << "->" << C << endl;
        return;
    }
    Hanoi(A, C, B, n-1); //先不考虑最下面的，因为它最大，不影响其它放置
    cout << "move:" << A << "->" << C << endl; //把最下面的挪过去
    Hanoi(B, A, C, n-1); //把剩下的挪过去

}
