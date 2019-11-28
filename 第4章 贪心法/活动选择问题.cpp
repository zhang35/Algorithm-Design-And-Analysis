#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event{
    int sTime;
    int fTime;
};

vector<Event> GreedySelect(vector<Event> events);
bool cmp(Event a, Event b);

int main()
{
    vector<Event> events = {{1,4},{3,5},{2,6},{5,7},{4,9},{5,9},{6,10},{8,11},{8,12},{2,13}};
    vector<Event> A = GreedySelect(events);
    cout << "maxNum is: \n" << A.size() << endl;
    cout << "arrangement is:" << endl;
    for (vector<Event>::iterator it=A.begin(); it!=A.end(); ++it){
        cout << it->sTime << "-" << it->fTime << " ";
    }
    cout << endl;
    return 0;
}
bool cmp(Event a, Event b){
    return a.fTime < b.fTime;
}

//4.1 活动选择问题，按结束时间排序能达到安排最多
vector<Event> GreedySelect(vector<Event> events){
    vector<Event> A;
    sort(events.begin(), events.end(), cmp); //需要include <algorithm>
    A.push_back(events[0]);
    int curFTime = events[0].fTime;
    for (vector<Event>::iterator it=events.begin()+1; it!=events.end(); ++it){
        if (it->sTime >= curFTime){
            A.push_back(*it);
            curFTime = it->fTime;
        }
    }
    return A;
}
