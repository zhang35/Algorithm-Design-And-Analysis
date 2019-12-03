#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task{
    int t;  //占用时间
    int d;  //希望完成时间
};

vector<int> Schedule(vector<Task> tasks);
bool cmp(Task a, Task b);

int main()
{
    vector<Task> tasks = {{5,10},{8,12},{4,15},{10,11},{3,20}};
    vector<int> A = Schedule(tasks);
    cout << "schedule(start time) is:" << endl;
    for (vector<int>::iterator it=A.begin(); it!=A.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
bool cmp(Task a, Task b){
    return a.d < b.d;
}

//4.2 调度问题，给定一串任务的服务时间t和希望完成时间d，延迟为服务结束时间减di。
//求调度f表示任务开始时间，使得最大延迟最小
vector<int> Schedule(vector<Task> tasks){
    int maxDelay = 0;
    vector<int> A;
    //按照希望完成时间排序即可
    sort(tasks.begin(), tasks.end(), cmp); //需要include <algorithm>
    A.push_back(0);
    int curTime = tasks[0].t;
    int curDelay = curTime - tasks[0].d;
    if (curDelay>maxDelay){
        maxDelay = curDelay;
    }
    for (vector<Task>::iterator it=tasks.begin()+1; it!=tasks.end(); ++it){
            A.push_back(curTime);
            curTime += it->t;
            curDelay = curTime - it->d;
            if (curDelay>maxDelay){
                maxDelay = curDelay;
            }
    }
    cout << "max delay is: \n" << maxDelay << endl;
    return A;
}
